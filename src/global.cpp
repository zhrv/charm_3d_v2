/**
 * Created by zhrv on 17.11.2020.
 * @author R.V.Zhalnin, zhalnin@gmail.com
 */

#include "global.h"

namespace charm {

    void delQuotes(String &s) {
        Index pos = 0;
        while ((pos = s.find("\"", pos)) != String::npos) {
            s.erase(pos, 1);
        }
    }


    Real matr3Det(Real a[3][3])
    {
        Real det_a = 0.;

        det_a += a[0][0] * a[1][1] * a[2][2];
        det_a += a[0][2] * a[1][0] * a[2][1];
        det_a += a[2][0] * a[0][1] * a[1][2];
        det_a -= a[0][2] * a[1][1] * a[2][0];
        det_a -= a[0][0] * a[1][2] * a[2][1];
        det_a -= a[0][1] * a[1][0] * a[2][2];

        return det_a;
    }

    void matr3Inv(Real a[3][3], Real a_inv[3][3])
    {
        Real a_[3][3];
        int i, j;
        Real det_a = matr3Det(a);

        //CHARM_ASSERT(det_a != 0.);

        a_[0][0] = a[1][1] * a[2][2] - a[1][2] * a[2][1];
        a_[0][1] = -a[0][1] * a[2][2] + a[0][2] * a[2][1];
        a_[0][2] = a[0][1] * a[1][2] - a[0][2] * a[1][1];

        a_[1][0] = -a[1][0] * a[2][2] + a[1][2] * a[2][0];
        a_[1][1] = a[0][0] * a[2][2] - a[0][2] * a[2][0];
        a_[1][2] = -a[0][0] * a[1][2] + a[0][2] * a[1][0];

        a_[2][0] = a[1][0] * a[2][1] - a[1][1] * a[2][0];
        a_[2][1] = -a[0][0] * a[2][1] + a[0][1] * a[2][0];
        a_[2][2] = a[0][0] * a[1][1] - a[0][1] * a[1][0];

        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                a_inv[i][j] = a_[i][j] / det_a;
            }
        }
    }

//        void matrInv(charm_matr_t a_src, charm_matr_t am)
//        {
//            int *mask;
//            Real fmaxval;
//            int maxind;
//            int tmpi;
//            Real tmp;
//            Real **a;
//            int N = CHARM_BASE_FN_COUNT;
//            int i, j, ni, nj;
//
//            mask = (int *) malloc(N * sizeof(int));//   new int[N];
//            a = (Real **) malloc(N * sizeof(Real * )); //new Real*[N];
//            for (i = 0; i < N; i++) {
//                a[i] = (Real *) malloc(N * sizeof(Real)); //new Real[N];
//                for (j = 0; j < N; j++) {
//                    a[i][j] = a_src[i][j];
//                }
//            }
//
//            for (i = 0; i < N; i++) {
//                for (j = 0; j < N; j++) {
//                    if (i == j) {
//                        am[i][j] = 1.0;
//                    } else {
//                        am[i][j] = 0.0;
//                    }
//                }
//            }
//            for (i = 0; i < N; i++) {
//                mask[i] = i;
//            }
//            for (i = 0; i < N; i++) {
//                maxind = i;
//                fmaxval = fabs(a[i][i]);
//                for (ni = i + 1; ni < N; ni++) {
//                    if (fabs(fmaxval) <= fabs(a[ni][i])) {
//                        fmaxval = fabs(a[ni][i]);
//                        maxind = ni;
//                    }
//                }
//                fmaxval = a[maxind][i];
//                CHARM_ASSERT(fmaxval != 0);
//                if (i != maxind) {
//                    for (nj = 0; nj < N; nj++) {
//                        tmp = a[i][nj];
//                        a[i][nj] = a[maxind][nj];
//                        a[maxind][nj] = tmp;
//
//                        tmp = am[i][nj];
//                        am[i][nj] = am[maxind][nj];
//                        am[maxind][nj] = tmp;
//                    }
//                    tmpi = mask[i];
//                    mask[i] = mask[maxind];
//                    mask[maxind] = tmpi;
//                }
//                Real aii = a[i][i];
//                for (j = 0; j < N; j++) {
//                    a[i][j] = a[i][j] / aii;
//                    am[i][j] = am[i][j] / aii;
//                }
//                for (ni = 0; ni < N; ni++) {
//                    if (ni != i) {
//                        Real fconst = a[ni][i];
//                        for (nj = 0; nj < N; nj++) {
//                            a[ni][nj] = a[ni][nj] - fconst * a[i][nj];
//                            am[ni][nj] = am[ni][nj] - fconst * am[i][nj];
//                        }
//                    }
//                }
//            }
//            /**/
//            for (i = 0; i < N; i++) {
//                if (mask[i] != i) {
//                    for (j = 0; j < N; j++) {
//                        tmp = a[i][j];
//                        a[i][j] = a[mask[i]][j];
//                        a[mask[i]][j] = tmp;
//                    }
//                }
//            }
//            /**/
//            for (i = 0; i < N; i++) {
//                free(a[i]);
//            }
//            free(a);
//            free(mask);
//
//        }

}