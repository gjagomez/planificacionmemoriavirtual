#ifndef VIRTUALMEMORY_H
#define VIRTUALMEMORY_H

#include <QQueue>
#include <QString>
#include <QVector>

enum class ReplacementPolicy {
    Fifo,
    Lru,
    Optimal
};

struct MemoryAccess
{
    int step = 0;
    int pageNumber = -1;
    int frameIndex = -1;
    bool tlbHit = false;
    bool pageFault = false;
    QVector<int> frameSnapshot;
    QVector<int> tlbSnapshot;
    QVector<int> tlbFrameSnapshot;
    QString explanation;
};

struct VirtualMemoryReport
{
    QVector<MemoryAccess> accesses;
    int pageFaults = 0;
    int tlbHits = 0;
    double hitRate = 0.0;
};

class VirtualMemorySimulator
{
public:
    VirtualMemorySimulator(int frames, int tlbEntries, ReplacementPolicy policy);

    void setReferenceString(const QVector<int> &references);
    VirtualMemoryReport runSimulation();

    void setPolicy(ReplacementPolicy policy);
    void setFrameCount(int frames);
    void setTlbSize(int tlbEntries);

private:
    int chooseFrameToReplaceOptimal(int currentIndex, int page) const;
    int chooseFrameToReplaceLru() const;
    int chooseFrameToReplaceFifo();
    void touchFrame(int frameIndex);
    void touchTlb(int entryIndex);

    QVector<int> m_references;
    int m_frames;
    int m_tlbEntries;
    ReplacementPolicy m_policy;

    QVector<int> m_frameTable;
    QVector<int> m_frameAges;
    QVector<int> m_tlbPages;
    QVector<int> m_tlbFrames;
    QVector<int> m_tlbUsage;
    QQueue<int> m_fifoQueue;
    int m_time = 0;
};

QString policyToText(ReplacementPolicy policy);

#endif // VIRTUALMEMORY_H
