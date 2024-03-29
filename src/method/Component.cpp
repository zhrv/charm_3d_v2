/**
 * Created by zhrv on 18.11.2020.
 * @author R.V.Zhalnin, zhalnin@gmail.com
 */

#include "Component.h"

namespace charm {
    Real Component::calcCp(Real t) {
        Real res = 0.;
        Real tt  = 1.;
        if (cpType == CP_CONST) {
            return cp[0];
        }
        else if (cpType == CP_POLYNOM) {
            for (auto cpi: cp){
                res += tt*(cpi);
                tt *= t;
            }
            return res;
        }
        else {
            return cp[0];
        }

    }

    Real Component::calcCpDt(Real t) {
        if (cpType != CP_POLYNOM) {
            throw Exception("Wrong call of function 'CALC_CP_DT'");
        }

        Real res = 0.;
        Real tt  = 1.;
        for (Index i= 1; i < cp.size(); i++) {
            res += tt*(cp[i])*i;
            tt *= t;
        }
        return res;
    }



}