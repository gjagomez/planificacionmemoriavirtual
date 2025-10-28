# Resultados, Metricas y Comparacion de Algoritmos  Proyecto Qt de Sistemas Operativos
Version 1.0 | Fecha: 25 de octubre de 2025

Este informe resume los experimentos reproducibles sobre los tres modulos del proyecto Qt (planificacion de CPU, semaforos y memoria virtual). Los casos se derivan de las muestras incluidas en el codigo fuente del repositorio.

## 1. Conjunto de casos de prueba
| Modulo | Escenario sintetico | Parametros clave | Fuente |
| ------ | ------------------- | ---------------- | ------ |
| PlanificadorQt | 4 procesos con llegadas escalonadas | Procesos definidos en `Memoriavirtual/principal.cpp:170` | `runSchedulingSimulation` |
| SemaforosQt | Productor-Consumidor | Productores=3, Consumidores=2, Buffer=5, Ciclos=3 (`principal.ui:463-526`) | `ProducerConsumerScenario::simulate` |
| MemoriaQt | Cadena de referencia | Referencias `7 0 1 2 0 3 0 4 2 3 0 3 2`, Marcos=3 (`principal.cpp:610-613`, `principal.ui:661-671`) | `VirtualMemorySimulator::runSimulation` |

## 2. Workloads sinteticos y trazas
- **Planificacion:** Ajustar el quantum a `4` en la interfaz (`principal.ui:55`) antes de ejecutar la simulacion para alinear el experimento con el escenario evaluado. La tabla de procesos se genera con `loadProcessSample()`.
- **Semaforos:** Establecer productores=3, consumidores=2, buffer=5 y ciclos=3 en la pestana de concurrencia. Cada ciclo recorre primero a los productores y luego a los consumidores, tal como lo implementa `ProducerConsumerScenario`.
- **Memoria virtual:** Usar la cadena de referencia proporcionada por `loadReferenceSample()` y fijar marcos=3, TLB=0 para aislar el efecto de las politicas FIFO, LRU y OPT.

## 3. Resultados de Planificacion de CPU (Quantum = 4)
| Algoritmo | Espera prom. (ms) | Retorno prom. (ms) | Respuesta prom. (ms) | Uso CPU (%) |
| --------- | ----------------- | ------------------ | -------------------- | ----------- |
| FCFS | 4.25 | 8.25 | 4.25 | 100 |
| SJF | 3.25 | 7.25 | 3.25 | 100 |
| SRTF | 3.00 | 7.00 | 1.75 | 100 |
| Round Robin (q=4) | 5.75 | 9.75 | 3.00 | 100 |
| Prioridades | 3.50 | 7.50 | 3.50 | 100 |

**Linea de tiempo (Gantt simplificado):**
- FCFS: P1 [0-6] -> P2 [6-9] -> P3 [9-14] -> P4 [14-16]
- SJF: P1 [0-6] -> P4 [6-8] -> P2 [8-11] -> P3 [11-16]
- SRTF: P1 [0-2] -> P2 [2-5] -> P1 [5-6] -> P4 [6-8] -> P1 [8-11] -> P3 [11-16]
- RR (q=4): P1 [0-4] -> P2 [4-7] -> P3 [7-11] -> P1 [11-13] -> P4 [13-15] -> P3 [15-16]
- Prioridades: P1 [0-6] -> P2 [6-9] -> P4 [9-11] -> P3 [11-16]

**Conclusiones parciales:** SRTF minimiza la espera y la respuesta promedio al adelantar ejecuciones cortas, mientras que Round Robin entrega la mejor respuesta inicial sin hambruna pero incrementa la espera total. FCFS y Prioridades quedan como referencias de baja y media complejidad respectivamente.

## 4. Resultados de Concurrencia con Semaforos
Escenario Productor-Consumidor (3P, 2C, buffer 5, 3 ciclos):
- Mensajes producidos: 9 operaciones totales (3 por ciclo).
- Mensajes consumidos: 6 operaciones (2 por ciclo), quedan 3 elementos en el buffer.
- Bloqueos: no se registran bloqueos (`wait(empty)` y `wait(full)` nunca se disparan porque la capacidad disponible es suficiente).
- Balance de semaforos: `empty` final = 2, `full` final = 3, `mutex` permanece limitado a 1.

**Conclusiones parciales:** El sistema opera en estado estable; la diferencia entre produccion y consumo revela la acumulacion esperada en el buffer. Para estudiar saturacion se recomienda incrementar los ciclos o reducir el tamano del buffer.

## 5. Resultados de Simulacion de Memoria Virtual
Politicas evaluadas con 3 marcos y TLB deshabilitado:
| Politica | Fallos de pagina | Tasa de fallos (%) | Notas |
| -------- | ---------------- | ------------------ | ----- |
| FIFO | 10 | 76.9 | Sensible a la posicion de referencia, Mayor efecto Belady |
| LRU | 9 | 69.2 | Mejora al aprovechar reutilizacion reciente |
| OPT | 7 | 53.8 | Limite teorico inferior de fallos para esta traza |

**Conclusiones parciales:** La traza sintetica favorece a estrategias con conocimiento del futuro (OPT) o historia reciente (LRU). FIFO exhibe el peor rendimiento debido a reemplazos prematuros.

## 6. Comparacion y recomendaciones finales
- **CPU:** Emplear SRTF para laboratorios orientados a minimizar tiempos promedio. SJF o Prioridades son alternativas sin preempcion compleja. Round Robin requiere revisar el quantum si se busca equilibrio entre respuesta y rendimiento.
- **Semaforos:** Documentar la cantidad de ciclos y el backlog al reportar experimentos. Ajustar buffer y proporciones de productores/consumidores para generar bloqueos medibles.
- **Memoria:** OPT sirve como base de referencia; LRU es la mejor opcion implementada para cargas con localidad. FIFO solo debe usarse con fines didacticos.

## 7. Informe final
En conjunto, los simuladores Qt del proyecto demuestran el impacto de los parametros de configuracion en el rendimiento. Las metricas cuantitativas anteriores, junto con los escenarios reproducibles, permiten comparar algoritmos y fundamentar decisiones didacticas. Se recomienda capturar capturas de pantalla de la interfaz y exportar resultados CSV para complementar la evidencia experimental.
