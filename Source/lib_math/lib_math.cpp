//
//  lib_math.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/26.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "lib_math.hpp"

double lib_math::string_2_double(string s) {
    return atof(const_cast<const char *>(s.c_str()));
}

int lib_math::string_2_int(string s) {
    return atoi(const_cast<const char *>(s.c_str()));
}

vector<double> lib_math::dd_c(vector< map<string, string> > data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        string c = m["c"];
        if (c.size()) rt.push_back(string_2_double(c));
        else rt.push_back(string_2_double(m["close"]));
    }
    return rt;
}

vector<double> lib_math::dd_o(vector< map<string, string> > data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        string o = m["o"];
        if (o.size()) rt.push_back(string_2_double(o));
        else rt.push_back(string_2_double(m["open"]));
    }
    return rt;
}

vector<double> lib_math::dd_l(vector< map<string, string> > data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        string l = m["l"];
        if (l.size()) rt.push_back(string_2_double(l));
        else rt.push_back(string_2_double(m["low"]));
    }
    return rt;
}

vector<double> lib_math::dd_h(vector< map<string, string> > data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        string h = m["h"];
        if (h.size()) rt.push_back(string_2_double(h));
        else rt.push_back(string_2_double(m["high"]));
    }
    return rt;
}

vector<double> lib_math::dd_ma(vector<double> data, size_t n) {
    std::vector<double> rt;
    if (n < 1) {
        return rt;
    }
    double t = 0;
    for (size_t i = 0; i < data.size(); i++) {
        t += data[i];
        if (i < n - 1) {
            rt.push_back(t / (i+1));
        } else {
            if (i >= n) t -= data[i - n];
            double v = t / n;
            rt.push_back(v);
        }
    }
    return rt;
}

vector<double> lib_math::dd_ema(vector<double> data, size_t n) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        if (i == 0) rt.push_back(data[i]);
        else {
            double v = data[i] * 2.f/(n+1.f) + rt.back() * (n-1.f)/(n+1.f);
            rt.push_back(v);
        }
    }
    return rt;
}

vector<double> lib_math::dd_sma(vector<double> data, size_t n, size_t m) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        if (i == 0) rt.push_back(data[i]);
        else {
            double v = data[i] * m/(n+0.f) + rt.back() * (n-m+0.f)/(n+0.f);
            rt.push_back(v);
        }
    }
    return rt;
}

vector<double> lib_math::dd_abs(vector<double> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        rt.push_back(fabs(data[i]));
    }
    return rt;
}

vector<double> lib_math::dd_max(vector<double> v1, vector<double> v2) {
    std::vector<double> rt;
    for (size_t i = 0; i < v1.size() && i < v2.size(); i++) {
        rt.push_back(v1[i] > v2[i] ? v1[i] : v2[i]);
    }
    return rt;
}

vector<double> lib_math::dd_min(vector<double> v1, vector<double> v2) {
    std::vector<double> rt;
    for (size_t i = 0; i < v1.size() && i < v2.size(); i++) {
        rt.push_back(v1[i] < v2[i] ? v1[i] : v2[i]);
    }
    return rt;
}

vector<double> lib_math::dd_std(vector<double> v1, size_t n) {
    std::vector<double> rt;
    std::vector<double> ma = lib_math::dd_ma(v1, n);
    for (size_t i = 0; i < ma.size() && i < v1.size(); i++) {
        double total = 0;
        size_t cnt = 0;
        for (size_t j = 0; j < n; j++) {
            if (i >= j) {
                total += pow(v1[i-j] - ma[i], 2);
                cnt ++;
            }
        }
        double val = sqrt(total/cnt);
        rt.push_back(val);
    }
    return rt;
}

vector<double> lib_math::dd_is_lastbar(vector< map<string, string> > data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        if (i == data.size() - 1) rt.push_back(1);
        else rt.push_back(0);
    }
    return rt;
}

vector<double> lib_math::dd_ref(vector<double> data, vector<double> n) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size() && i < n.size(); i++) {
        if (i >= n[i]) rt.push_back(data[i - n[i]]);
        else rt.push_back(0);
    }
    return rt;
}

vector<double> lib_math::dd_refx(vector<double> data, vector<double> n) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size() && i < n.size(); i++) {
        if (i + n[i] < data.size()) rt.push_back(data[i + n[i]]);
        else rt.push_back(0);
    }
    return rt;
}

vector<double> lib_math::dd_hhv(vector<double> data, size_t n) {
    std::vector<double> rt;
    std::deque<long> deq;
    for (long i = 0; i < data.size(); i++) {
        long x = i - n;
        if (deq.size() > 0 && deq.front() <= x) {
            deq.pop_front();
        }
        while (deq.size() > 0 && data[deq.back()] < data[i]) {
            deq.pop_back();
        }
        deq.push_back(i);
        rt.push_back(data[deq.front()]);
    }
    return rt;
}

vector<double> lib_math::dd_hhv(vector<double> data, vector<double> n) {
    std::vector<double> rt;
    for (long i = 0; i < data.size() && i < n.size(); i++) {
        if (n[i] <= 0) {
            rt.push_back(data[i]);
        } else {
            double h = DBL_MIN;
            for (long j = 0; j < n[i]; j++) {
                if (i - j >= 0 && h < data[i - j]) h = data[i - j];
            }
            rt.push_back(h);
        }
    }
    return rt;
}

vector<double> lib_math::dd_llv(vector<double> data, size_t n) {
    std::vector<double> rt;
    std::deque<long> deq;
    for (long i = 0; i < data.size(); i++) {
        long x = i - n;
        if (deq.size() > 0 && deq.front() <= x) {
            deq.pop_front();
        }
        while (deq.size() > 0 && data[deq.back()] > data[i]) {
            deq.pop_back();
        }
        deq.push_back(i);
        rt.push_back(data[deq.front()]);
    }
    return rt;
}

vector<double> lib_math::dd_llv(vector<double> data, vector<double> n) {
    std::vector<double> rt;
    for (long i = 0; i < data.size() && i < n.size(); i++) {
        if (n[i] <= 0) {
            rt.push_back(data[i]);
        } else {
            double l = DBL_MAX;
            for (long j = 0; j < n[i]; j++) {
                if (i - j >= 0 && l > data[i - j]) l = data[i - j];
            }
            rt.push_back(l);
        }
    }
    return rt;
}

vector<double> lib_math::dd_eif(vector<double> data, vector<double> v1, vector<double> v2) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size() && i < v1.size() && i < v2.size(); i++) {
        rt.push_back(data[i] != 0 ? v1[i] : v2[i]);
    }
    return rt;
}

vector<double> lib_math::dd_cross(vector<double> v1, vector<double> v2) {
    std::vector<double> rt;
    double pv1 = 0.0, pv2 = 0.0;
    for (size_t i = 0; i < v1.size() && i < v2.size(); i++) {
        if (i == 0) {
            rt.push_back(0);
        } else {
            rt.push_back((pv1 < pv2 && v1[i] >= v2[i]) ? 1 : 0);
        }
        pv1 = v1[i];
        pv2 = v2[i];
    }
    return rt;
}

vector<double> lib_math::dd_barslast(vector<double> data) {
    std::vector<double> rt;
    long cnt = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if (i == 0) {
            cnt = 0;
            rt.push_back(0);
        } else {
            if (data[i] == 0) {
                rt.push_back(++cnt);
            } else {
                cnt = 0;
                rt.push_back(cnt);
            }
        }
    }
    return rt;
}

vector<double> lib_math::dd_backset(vector<double> data, vector<double> n) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        rt.push_back(0);
    }
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] != 0) {
            for (size_t j = 0; j < n[i]; j++) {
                if (i < j) continue;
                rt[i - j] = 1;
            }
        } else {
            rt[i] = 0;
        }
    }
    return rt;
}

vector<double> lib_math::dd_value_when(vector<double> data, vector<double> val) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size() && i < val.size(); i++) {
        if (data[i] != 0) {
            rt.push_back(val[i]);
        } else {
            rt.push_back(rt.empty() ? val[i] : rt.back());
        }
    }
    return rt;
}
