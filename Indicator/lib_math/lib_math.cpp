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

vector<double> lib_math::c(vector<map<string, string>> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        rt.push_back(string_2_double(m["c"]));
    }
    return rt;
}

vector<double> lib_math::o(vector<map<string, string>> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        rt.push_back(string_2_double(m["o"]));
    }
    return rt;
}

vector<double> lib_math::l(vector<map<string, string>> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        rt.push_back(string_2_double(m["l"]));
    }
    return rt;
}

vector<double> lib_math::h(vector<map<string, string>> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        map<string, string> m = data[i];
        rt.push_back(string_2_double(m["h"]));
    }
    return rt;
}

vector<double> lib_math::ma(vector<double> data, size_t n) {
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
            if (i - n >= 0) t -= data[i - n];
            double v = t / n;
            rt.push_back(v);
        }
    }
    return rt;
}

vector<double> lib_math::ma(vector<double> data, vector<double> n) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        double t = 0;
        size_t cnt = 0;
        for (size_t j = 0; j < n[i]; j++) {
            if (i >= j) {
                t += data[i - j];
                cnt++;
            }
        }
        rt.push_back(t / cnt);
    }
    return rt;
}

vector<double> lib_math::is_lastbar(vector<map<string, string>> data) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        if (i == data.size() - 1) rt.push_back(1);
        else rt.push_back(0);
    }
    return rt;
}

vector<double> lib_math::ref(vector<double> data, size_t n) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        if (i >= n) rt.push_back(data[i - n]);
        else rt.push_back(0);
    }
    return rt;
}

vector<double> lib_math::ref(vector<double> data, vector<double> n) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size() && i < n.size(); i++) {
        if (i >= n[i]) rt.push_back(data[i - n[i]]);
        else rt.push_back(0);
    }
    return rt;
}

vector<double> lib_math::hhv(vector<double> data, size_t n) {
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

vector<double> lib_math::hhv(vector<double> data, vector<double> n) {
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

vector<double> lib_math::llv(vector<double> data, size_t n) {
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

vector<double> lib_math::llv(vector<double> data, vector<double> n) {
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

vector<double> lib_math::eif(vector<double> data, vector<double> v1, vector<double> v2) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size() && i < v1.size() && i < v2.size(); i++) {
        rt.push_back(data[i] != 0 ? v1[i] : v2[i]);
    }
    return rt;
}

vector<double> lib_math::barslast(vector<double> data) {
    std::vector<double> rt;
    long cnt = -1;
    for (size_t i = 0; i < data.size(); i++) {
        double val = data[i];
        if (cnt < 0) {
            cnt = 0;
            rt.push_back(0);
            if (val != 0) cnt = 0;
            continue;
        }
        rt.push_back(++cnt);
        if (val != 0) cnt = 0;
    }
    return rt;
}

vector<double> lib_math::backset(vector<double> data, size_t n) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        rt.push_back(0);
    }
    for (long i = data.size() - 1; i >= 0; i--) {
        if (data[i] != 0) {
            for (size_t j = 0; j < n; j++) {
                if (i < j) continue;
                rt[i - j] = 0;
                i--;
            }
        } else {
            rt[i] = 0;
        }
    }
    return rt;
}

vector<double> lib_math::backset(vector<double> data, vector<double> n) {
    std::vector<double> rt;
    for (size_t i = 0; i < data.size(); i++) {
        rt.push_back(0);
    }
    for (size_t i = data.size() - 1; i >= 0 && i < n.size(); i--) {
        if (data[i] != 0) {
            for (size_t j = 0; j < n[i]; j++) {
                if (i < j) continue;
                rt[i - j] = 0;
                i--;
            }
        } else {
            rt[i] = 0;
        }
    }
    return rt;
}

vector<double> lib_math::value_when(vector<double> data, vector<double> val) {
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
