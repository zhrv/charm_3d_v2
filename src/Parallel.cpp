/*
 *     ________  _____    ____  __  ___    _____ ____
 *    / ____/ / / /   |  / __ \/  |/  /   |__  // __ \  __    __
 *   / /   / /_/ / /| | / /_/ / /|_/ /     /_ </ / / /_/ /___/ /_
 *  / /___/ __  / ___ |/ _, _/ /  / /    ___/ / /_/ /_  __/_  __/
 *  \____/_/ /_/_/  |_/_/ |_/_/  /_/____/____/_____/ /_/   /_/
 *
 */

#include <mesh/Mesh.h>
#include <method/global/Config.h>
#include "Parallel.h"


namespace charm {

    MPI_Status mpiSt;
    Int Parallel::procCount = 0;
    Int Parallel::procId = 0;

    void Parallel::init(Int* argc, char*** argv)
    {
        MPI_Init(argc, argv);
        MPI_Comm_size(MPI_COMM_WORLD, &procCount);
        MPI_Comm_rank(MPI_COMM_WORLD, &procId);
    }

    void Parallel::done()
    {
        MPI_Finalize();
    }

    void Parallel::send(Int pid, Int tag, Int n, Real* x)
    {
        MPI_Send(x, n, MPI_DOUBLE, pid, tag, MPI_COMM_WORLD);
    }

    void Parallel::send(Int pid, Int tag, Int n, Int* x)
    {
        MPI_Send(x, n, MPI_INT, pid, tag, MPI_COMM_WORLD);
    }


    void Parallel::recv(Int pid, Int tag, Int n, Real* x)
    {
        MPI_Recv(x, n, MPI_DOUBLE, pid, tag, MPI_COMM_WORLD, &mpiSt);
    }

    void Parallel::recv(Int pid, Int tag, Int n, Int* x)
    {
        MPI_Recv(x, n, MPI_INT, pid, tag, MPI_COMM_WORLD, &mpiSt);
    }

    void Parallel::bcast(Int root, Int n, Int* x) {
        MPI_Bcast(x, n, MPI_INT, root, MPI_COMM_WORLD);
    }

    void Parallel::bcast(Int root, Int n, Index* x) {
        MPI_Bcast(x, n, MPI_LONG_INT, root, MPI_COMM_WORLD);
    }

    void Parallel::bcast(Int root, Int n, Real* x)
    {
        MPI_Bcast(x, n, MPI_DOUBLE, root, MPI_COMM_WORLD);
    }

    void Parallel::send(Int pid, Int tag, Int n, Byte *data) {
        MPI_Send(data, n, MPI_CHAR, pid, tag, MPI_COMM_WORLD);
    }

    void Parallel::recv(Int pid, Int tag, Int n, Byte *data) {
        MPI_Recv(data, n, MPI_CHAR, pid, tag, MPI_COMM_WORLD, &mpiSt);
    }

    void Parallel::send(Int pid, Int tag, Int n, Vector *data) {
        ArrayReal x(n*3);
        for (Index i = 0; i < n; i++) {
            x[i*3+0] = data[i][0];
            x[i*3+1] = data[i][1];
            x[i*3+2] = data[i][2];
        }
        MPI_Send(x.data(), n*3, MPI_DOUBLE, pid, tag, MPI_COMM_WORLD);
    }

    void Parallel::recv(Int pid, Int tag, Int n, Vector *data) {
        ArrayReal x(n*3);
        MPI_Recv(x.data(), n*3, MPI_DOUBLE, pid, tag, MPI_COMM_WORLD, &mpiSt);
        for (Index i = 0; i < n; i++) {
            data[i][0] = x[i*3+0];
            data[i][1] = x[i*3+1];
            data[i][2] = x[i*3+2];
        }
    }

    void Parallel::bcast(Int root, Int n, Vector* data)
    {
        ArrayReal x(n*3);
        if (procId == root) {
            for (Index i = 0; i < n; i++) {
                x[i * 3 + 0] = data[i][0];
                x[i * 3 + 1] = data[i][1];
                x[i * 3 + 2] = data[i][2];
            }
        }
        MPI_Bcast(x.data(), n, MPI_DOUBLE, root, MPI_COMM_WORLD);
        if (procId != root) {
            for (Index i = 0; i < n; i++) {
                data[i][0] = x[i * 3 + 0];
                data[i][1] = x[i * 3 + 1];
                data[i][2] = x[i * 3 + 2];
            }
        }
    }

    void Parallel::min(Real *x) {
        Real tmp;
        MPI_Allreduce(x, &tmp, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
        *x = tmp;
    }

    void Parallel::max(Real *x) {
        Real tmp;
        MPI_Allreduce(x, &tmp, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
        *x = tmp;
    }

    void Parallel::sum(Real *x) {
        Real tmp;
        MPI_Allreduce(x, &tmp, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        *x = tmp;
    }

    void Parallel::exchange(ArrayVector &field) {
        Mesh& mesh = Config::getMesh();
        assert(field.size() == mesh.getCellsCountWithGhost() && "Wrong fields count for exchange.");

        for (int p = 0; p < Parallel::procCount; p++) {
            if (p < Parallel::procId) {
                if (mesh.recvCount[p] > 0) {
                    ArrayVector buf(mesh.recvCount[p]);
                    Parallel::recv(p, 0, mesh.recvCount[p], buf.data());
                    for (Index i = 0; i < mesh.recvCount[p]; i++) {
                        field[mesh.recvShift[p]+i] = buf[i];
                    }
                }
                int n = mesh.sendInd[p].size();
                if (n > 0) {
                    ArrayVector buf(n);
                    for (int i = 0; i < n; i++) {
                        buf[i] = field[mesh.sendInd[p][i]];
                    }
                    Parallel::send(p, 1, n, buf.data());
                }
            }
            else if (p > Parallel::procId) {
                int n = mesh.sendInd[p].size();
                if (n > 0) {
                    ArrayVector buf(n);
                    for (int i = 0; i < n; i++) {
                        buf[i] = field[mesh.sendInd[p][i]];
                    }
                    Parallel::send(p, 0, n, buf.data());
                }
                if (mesh.recvCount[p] > 0) {
                    ArrayVector buf(mesh.recvCount[p]);
                    Parallel::recv(p, 1, mesh.recvCount[p], buf.data());
                    for (Index i = 0; i < mesh.recvCount[p]; i++) {
                        field[mesh.recvShift[p]+i] = buf[i];
                    }
                }
            }
        }
        Parallel::barrier();

    }


    void Parallel::exchange(ArrayReal &field) {
        Mesh& mesh = Config::getMesh();
        assert(field.size() == mesh.getCellsCountWithGhost() && "Wrong fields count for exchange.");

        for (int p = 0; p < Parallel::procCount; p++) {
            if (p < Parallel::procId) {
                if (mesh.recvCount[p] > 0) {
                    ArrayReal buf(mesh.recvCount[p]);
                    Parallel::recv(p, 0, mesh.recvCount[p], buf.data());
                    for (Index i = 0; i < mesh.recvCount[p]; i++) {
                        field[mesh.recvShift[p]+i] = buf[i];
                    }
                }
                int n = mesh.sendInd[p].size();
                if (n > 0) {
                    ArrayReal buf(n);
                    for (int i = 0; i < n; i++) {
                        buf[i] = field[mesh.sendInd[p][i]];
                    }
                    Parallel::send(p, 1, n, buf.data());
                }
            }
            else if (p > Parallel::procId) {
                int n = mesh.sendInd[p].size();
                if (n > 0) {
                    ArrayReal buf(n);
                    for (int i = 0; i < n; i++) {
                        buf[i] = field[mesh.sendInd[p][i]];
                    }
                    Parallel::send(p, 0, n, buf.data());
                }
                if (mesh.recvCount[p] > 0) {
                    ArrayReal buf(mesh.recvCount[p]);
                    Parallel::recv(p, 1, mesh.recvCount[p], buf.data());
                    for (Index i = 0; i < mesh.recvCount[p]; i++) {
                        field[mesh.recvShift[p]+i] = buf[i];
                    }
                }
            }
        }
        Parallel::barrier();

    }


    void Parallel::exchange(Array<ArrayVector> &field) {
        Mesh& mesh = Config::getMesh();
        assert(field.size() == mesh.getCellsCountWithGhost() && "Wrong fields count for exchange.");

        Index compCount = Config::getCompCount();
        for (int p = 0; p < Parallel::procCount; p++) {
            if (p < Parallel::procId) {
                if (mesh.recvCount[p] > 0) {
                    ArrayVector buf(mesh.recvCount[p] * compCount);
                    Parallel::recv(p, 0, mesh.recvCount[p] * compCount, buf.data());
                    for (Index i = 0; i < mesh.recvCount[p]; i++) {
                        for (Index j = 0; j < compCount; j++) {
                            field[mesh.recvShift[p] + i][j] = buf[i*compCount+j];
                        }
                    }
                }
                int n = mesh.sendInd[p].size();
                if (n > 0) {
                    ArrayVector buf(n*compCount);
                    for (int i = 0; i < n; i++) {
                        for (Index j = 0; j < compCount; j++) {
                            buf[i*compCount+j] = field[mesh.sendInd[p][i]][j];
                        }
                    }
                    Parallel::send(p, 1, n*compCount, buf.data());
                }
            }
            else if (p > Parallel::procId) {
                int n = mesh.sendInd[p].size();
                if (n > 0) {
                    ArrayVector buf(n*compCount);
                    for (int i = 0; i < n; i++) {
                        for (Index j = 0; j < compCount; j++) {
                            buf[i*compCount+j] = field[mesh.sendInd[p][i]][j];
                        }
                    }
                    Parallel::send(p, 0, n*compCount, buf.data());
                }
                if (mesh.recvCount[p] > 0) {
                    ArrayVector buf(mesh.recvCount[p]*compCount);
                    Parallel::recv(p, 1, mesh.recvCount[p]*compCount, buf.data());
                    for (Index i = 0; i < mesh.recvCount[p]; i++) {
                        for (Index j = 0; j < compCount; j++) {
                            field[mesh.recvShift[p] + i][j] = buf[i*compCount+j];
                        }
                    }
                }
            }
        }
        Parallel::barrier();

    }


    void Parallel::exchange(Array<ArrayReal> &field) {
        Mesh& mesh = Config::getMesh();
        assert(field.size() == mesh.getCellsCountWithGhost() && "Wrong fields count for exchange.");

        Index compCount = Config::getCompCount();
        for (int p = 0; p < Parallel::procCount; p++) {
            if (p < Parallel::procId) {
                if (mesh.recvCount[p] > 0) {
                    ArrayReal buf(mesh.recvCount[p] * compCount);
                    Parallel::recv(p, 0, mesh.recvCount[p] * compCount, buf.data());
                    for (Index i = 0; i < mesh.recvCount[p]; i++) {
                        for (Index j = 0; j < compCount; j++) {
                            field[mesh.recvShift[p] + i][j] = buf[i*compCount+j];
                        }
                    }
                }
                int n = mesh.sendInd[p].size();
                if (n > 0) {
                    ArrayReal buf(n*compCount);
                    for (int i = 0; i < n; i++) {
                        for (Index j = 0; j < compCount; j++) {
                            buf[i*compCount+j] = field[mesh.sendInd[p][i]][j];
                        }
                    }
                    Parallel::send(p, 1, n * compCount, buf.data());
                }
            }
            else if (p > Parallel::procId) {
                int n = mesh.sendInd[p].size();
                if (n > 0) {
                    ArrayReal buf(n*compCount);
                    for (int i = 0; i < n; i++) {
                        for (Index j = 0; j < compCount; j++) {
                            buf[i*compCount+j] = field[mesh.sendInd[p][i]][j];
                        }
                    }
                    Parallel::send(p, 0, n * compCount, buf.data());
                }
                if (mesh.recvCount[p] > 0) {
                    ArrayReal buf(mesh.recvCount[p] * compCount);
                    Parallel::recv(p, 1, mesh.recvCount[p] * compCount, buf.data());
                    for (Index i = 0; i < mesh.recvCount[p]; i++) {
                        for (Index j = 0; j < compCount; j++) {
                            field[mesh.recvShift[p] + i][j] = buf[i*compCount+j];
                        }
                    }
                }
            }
        }
        Parallel::barrier();

    }



}