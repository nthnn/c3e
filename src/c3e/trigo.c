/*
 * Copyright 2024 Nathanne Isip
 * 
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 */

#include <c3e/trigo.h>

#include <assert.h>
#include <float.h>
#include <math.h>

static const c3e_number asymptotic_series[] = {
	0.08333333333,
	-0.00277777777,
	0.00079365079,
	-0.00059523809,
	0.00084175084,
	-0.00191752691,
	0.00641025641,
	-0.02955065359
};

static const c3e_number numcoeff_approx[] = {
    -1.71618513886549492533811E+0,
    2.47656508055759199108314E+1,
    -3.79804256470945635097577E+2,
    6.29331155312818442661052E+2,
    8.66966202790413211295064E+2,
    -3.14512729688483675254357E+4,
    -3.61444134186911729807069E+4,
    6.64561438202405440627855E+4
};

static const c3e_number dencoeff_approx[] = {
    -3.08402300119738975254353E+1,
    3.15350626979604161529144E+2,
    -1.01515636749021914166146E+3,
    -3.10777167157231109440444E+3,
    2.25381184209801510330112E+4,
    4.75584627752788110767815E+3,
    -1.34659959864969306392456E+5,
    -1.15132259675553483497211E+5
};

c3e_number c3e_radian_degrees(c3e_number x) {
    return (x * 180) / (c3e_number) PI;
}

c3e_number c3e_gamma(c3e_number x) {
    assert(x > 0.0);

    if(x < 0.001)
        return 1.0 / (x * (
            1.0 + 0.577215664901532860606512090 * x
        ));

    if(x < 12.0) {
        c3e_number y = x;
        bool lt_one = (y < 1.0);
        int n = 0;

        if(lt_one)
            y += 1.0;
        else {
            n = ((int) floor(y)) - 1;
            y -= n;
        }

        c3e_number numerator = 0.0,
            denominator = 1.0,
            z = y - 1;
        for(int i = 0; i < 8; i++) {
            numerator = (numerator + numcoeff_approx[i]) * z;
            denominator = denominator * z + dencoeff_approx[i];
        }

        c3e_number result = numerator / denominator + 1.0;
        if(lt_one)
            result /= y - 1.0;
        else for(int i = 0; i < n; i++)
            result *= y++;

        return result;
    }

    if(x > 171.624)
        return DBL_MAX * 2.0;

    return exp(c3e_log_gamma(x));
}

c3e_number c3e_log_gamma(c3e_number x) {
    assert(x > 0.0);

    if(x < 12.0)
        return log(fabs(c3e_gamma(x)));

    c3e_number z = 1.0 / (x * x), sum = asymptotic_series[7];
    for(int i = 6; i >= 0; i--) {
        sum *= z;
        sum += asymptotic_series[i];
    }

    return (x - 0.5) * log(x) - x +
        0.91893853320467274178032973640562 +
        (sum / x);
}