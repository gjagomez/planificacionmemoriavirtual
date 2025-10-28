#include "virtualmemory.h"

#include <algorithm>
#include <limits>

VirtualMemorySimulator::VirtualMemorySimulator(int frames, int tlbEntries, ReplacementPolicy policy)
    : m_frames(std::max(1, frames))
    , m_tlbEntries(std::max(0, tlbEntries))
    , m_policy(policy)
{
    setFrameCount(frames);
    setTlbSize(tlbEntries);
}

void VirtualMemorySimulator::setReferenceString(const QVector<int> &references)
{
    m_references = references;
}

VirtualMemoryReport VirtualMemorySimulator::runSimulation()
{
    VirtualMemoryReport report;
    report.accesses.reserve(m_references.size());
    m_time = 0;

    m_frameTable = QVector<int>(m_frames, -1);
    m_frameAges = QVector<int>(m_frames, 0);
    m_fifoQueue.clear();

    m_tlbPages = QVector<int>(m_tlbEntries, -1);
    m_tlbFrames = QVector<int>(m_tlbEntries, -1);
    m_tlbUsage = QVector<int>(m_tlbEntries, 0);

    int pageFaults = 0;
    int tlbHits = 0;

    for (int index = 0; index < m_references.size(); ++index) {
        ++m_time;
        const int page = m_references[index];

        MemoryAccess access;
        access.step = index;
        access.pageNumber = page;

        int frameIndex = -1;
        int tlbIndex = -1;

        for (int t = 0; t < m_tlbEntries; ++t) {
            if (m_tlbPages[t] == page) {
                tlbIndex = t;
                break;
            }
        }

        if (tlbIndex != -1) {
            access.tlbHit = true;
            ++tlbHits;
            frameIndex = m_tlbFrames[tlbIndex];
            touchTlb(tlbIndex);
            touchFrame(frameIndex);
            access.explanation = QStringLiteral("TLB hit -> frame %1").arg(frameIndex);
        } else {
            for (int f = 0; f < m_frames; ++f) {
                if (m_frameTable[f] == page) {
                    frameIndex = f;
                    break;
                }
            }

            if (frameIndex != -1) {
                access.explanation = QStringLiteral("TLB miss, pagina ya en marco %1").arg(frameIndex);
                touchFrame(frameIndex);
            } else {
                access.pageFault = true;
                ++pageFaults;
                for (int f = 0; f < m_frames; ++f) {
                    if (m_frameTable[f] == -1) {
                        frameIndex = f;
                        if (m_policy == ReplacementPolicy::Fifo && !m_fifoQueue.contains(f)) {
                            m_fifoQueue.enqueue(f);
                        }
                        break;
                    }
                }
                if (frameIndex == -1) {
                    switch (m_policy) {
                    case ReplacementPolicy::Fifo:
                        frameIndex = chooseFrameToReplaceFifo();
                        break;
                    case ReplacementPolicy::Lru:
                        frameIndex = chooseFrameToReplaceLru();
                        break;
                    case ReplacementPolicy::Optimal:
                        frameIndex = chooseFrameToReplaceOptimal(index, page);
                        break;
                    }
                }

                access.explanation = QStringLiteral("Falta de pagina -> carga en marco %1 (%2)")
                                          .arg(frameIndex)
                                          .arg(policyToText(m_policy));
                m_frameTable[frameIndex] = page;
                touchFrame(frameIndex);
            }

            if (m_tlbEntries > 0) {
                int slot = -1;
                for (int t = 0; t < m_tlbEntries; ++t) {
                    if (m_tlbPages[t] == -1) {
                        slot = t;
                        break;
                    }
                }
                if (slot == -1) {
                    int lruIndex = 0;
                    for (int t = 1; t < m_tlbEntries; ++t) {
                        if (m_tlbUsage[t] < m_tlbUsage[lruIndex]) {
                            lruIndex = t;
                        }
                    }
                    slot = lruIndex;
                }
                m_tlbPages[slot] = page;
                m_tlbFrames[slot] = frameIndex;
                touchTlb(slot);
            }
        }

        access.frameIndex = frameIndex;
        access.frameSnapshot = m_frameTable;
        access.tlbSnapshot = m_tlbPages;
        access.tlbFrameSnapshot = m_tlbFrames;
        report.accesses.push_back(access);
    }

    report.pageFaults = pageFaults;
    report.tlbHits = tlbHits;
    report.hitRate = report.accesses.isEmpty() ? 0.0 : static_cast<double>(tlbHits) / report.accesses.size();
    return report;
}

void VirtualMemorySimulator::setPolicy(ReplacementPolicy policy)
{
    m_policy = policy;
}

void VirtualMemorySimulator::setFrameCount(int frames)
{
    m_frames = std::max(1, frames);
}

void VirtualMemorySimulator::setTlbSize(int tlbEntries)
{
    m_tlbEntries = std::max(0, tlbEntries);
}

int VirtualMemorySimulator::chooseFrameToReplaceOptimal(int currentIndex, int page) const
{
    (void)page;
    int farthest = -1;
    int bestFrame = 0;
    for (int f = 0; f < m_frameTable.size(); ++f) {
        const int framePage = m_frameTable[f];
        int nextUse = std::numeric_limits<int>::max();
        for (int look = currentIndex + 1; look < m_references.size(); ++look) {
            if (m_references[look] == framePage) {
                nextUse = look;
                break;
            }
        }
        if (nextUse == std::numeric_limits<int>::max()) {
            return f;
        }
        if (nextUse > farthest) {
            farthest = nextUse;
            bestFrame = f;
        }
    }
    return bestFrame;
}

int VirtualMemorySimulator::chooseFrameToReplaceLru() const
{
    int oldestTime = std::numeric_limits<int>::max();
    int oldestFrame = 0;
    for (int f = 0; f < m_frameAges.size(); ++f) {
        if (m_frameAges[f] < oldestTime) {
            oldestTime = m_frameAges[f];
            oldestFrame = f;
        }
    }
    return oldestFrame;
}

int VirtualMemorySimulator::chooseFrameToReplaceFifo()
{
    if (m_fifoQueue.size() < m_frames) {
        for (int f = 0; f < m_frames; ++f) {
            if (!m_fifoQueue.contains(f)) {
                m_fifoQueue.enqueue(f);
                return f;
            }
        }
    }
    const int frame = m_fifoQueue.dequeue();
    m_fifoQueue.enqueue(frame);
    return frame;
}

void VirtualMemorySimulator::touchFrame(int frameIndex)
{
    if (frameIndex >= 0 && frameIndex < m_frameAges.size()) {
        m_frameAges[frameIndex] = m_time;
    }
}

void VirtualMemorySimulator::touchTlb(int entryIndex)
{
    if (entryIndex >= 0 && entryIndex < m_tlbUsage.size()) {
        m_tlbUsage[entryIndex] = m_time;
    }
}

QString policyToText(ReplacementPolicy policy)
{
    switch (policy) {
    case ReplacementPolicy::Fifo:
        return QStringLiteral("FIFO");
    case ReplacementPolicy::Lru:
        return QStringLiteral("LRU");
    case ReplacementPolicy::Optimal:
        return QStringLiteral("OPT");
    }
    return QStringLiteral("Desconocida");
}
