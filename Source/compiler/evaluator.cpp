//
//  evaluator.cpp
//  Indicator
//
//  Created by 许龙 on 2019/12/26.
//  Copyright © 2019 许龙. All rights reserved.
//

#include "evaluator.hpp"
#include "lib_math.hpp"
#include "lib_draw.hpp"

static double draw_null = -1000000000.f;

std::vector<double> evaluator::_call_function(std::string name, ast_node::ptr root) {
    std::vector<double> rt;
    if (name.compare("C") == 0 || name.compare("CLOSE") == 0) {
        std::map< std::string, std::vector<double> >::iterator iter = variables.find("C");
        if (iter != variables.end()) {
            rt = iter->second;
        } else {
            rt = lib_math::dd_c(data);
            if (rt.size()) {
                variables.insert({"C", rt});
            }
        }
    } else if (name.compare("O") == 0 || name.compare("OPEN") == 0) {
        std::map< std::string, std::vector<double> >::iterator iter = variables.find("O");
        if (iter != variables.end()) {
            rt = iter->second;
        } else {
            rt = lib_math::dd_o(data);
            if (rt.size()) {
                variables.insert({"O", rt});
            }
        }
    } else if (name.compare("H") == 0 || name.compare("HIGH") == 0) {
        std::map< std::string, std::vector<double> >::iterator iter = variables.find("H");
        if (iter != variables.end()) {
            rt = iter->second;
        } else {
            rt = lib_math::dd_h(data);
            if (rt.size()) {
                variables.insert({"H", rt});
            }
        }
    } else if (name.compare("L") == 0 || name.compare("LOW") == 0) {
        std::map< std::string, std::vector<double> >::iterator iter = variables.find("L");
        if (iter != variables.end()) {
            rt = iter->second;
        } else {
            rt = lib_math::dd_l(data);
            if (rt.size()) {
                variables.insert({"L", rt});
            }
        }
    } else if (name.compare("ISLASTBAR") == 0) {
        rt = lib_math::dd_is_lastbar(data);
        
    }  else if (name.compare("MA") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));  // just digit literal
        if (v2.size() > 0) {
            rt = lib_math::dd_ma(v1, (size_t)v2[0]);
        }
    } else if (name.compare("EMA") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        if (v2.size() > 0) {
            rt = lib_math::dd_ema(v1, (size_t)v2[0]);
        }
    } else if (name.compare("SMA") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        std::vector<double> v3 = _evaluate(root->get_child(2));
        if (v2.size() > 0 && v3.size() > 0) {
            rt = lib_math::dd_sma(v1, (size_t)v2[0], (size_t)v3[0]);
        }
    } else if (name.compare("REF") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        rt = lib_math::dd_ref(v1, v2);
        
    } else if (name.compare("REFX") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        rt = lib_math::dd_refx(v1, v2);
        
    } else if (name.compare("HHV") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        if (v2.size() == 1) {
            rt = lib_math::dd_hhv(v1, (size_t)v2[0]);
        } else {
            rt = lib_math::dd_hhv(v1, v2);
        }
    } else if (name.compare("LLV") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        if (v2.size() == 1) {
            rt = lib_math::dd_llv(v1, (size_t)v2[0]);
        } else {
            rt = lib_math::dd_llv(v1, v2);
        }
    } else if (name.compare("AVEDEV") == 0) {
        std::cout << "Not implement func name : " << name << std::endl;
        
    } else if (name.compare("STD") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        if (v2.size() > 0) {
            rt = lib_math::dd_std(v1, (size_t)v2[0]);
        }
    } else if (name.compare("CROSS") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        rt = lib_math::dd_cross(v1, v2);
        
    } else if (name.compare("IF") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        std::vector<double> v3 = _evaluate(root->get_child(2));
        rt = lib_math::dd_eif(v1, v2, v3);
        
    } else if (name.compare("BARSLAST") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        rt = lib_math::dd_barslast(v1);
        
    } else if (name.compare("BACKSET") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        rt = lib_math::dd_backset(v1, v2);
        
    } else if (name.compare("VALUEWHEN") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        rt = lib_math::dd_value_when(v1, v2);
        
    } else if (name.compare("IF") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        std::vector<double> v3 = _evaluate(root->get_child(2));
        rt = lib_math::dd_eif(v1, v2, v3);
        
    } else if (name.compare("MAX") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        rt = lib_math::dd_max(v1, v2);
        
    } else if (name.compare("MIN") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        rt = lib_math::dd_min(v1, v2);
        
    } else if (name.compare("ABS") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        rt = lib_math::dd_abs(v1);
        
    } else {
        std::cout << "Not implement func name : " << name << std::endl;
    }
    return rt;
}

vector< map<string, string> > evaluator::_draw_function(std::string name, ast_node::ptr root) {
    vector< map<string, string> > rt;
    if (name.compare("DRAWTEXT") == 0) {
        std::vector<double> v1 = _evaluate(root->get_child(0));
        std::vector<double> v2 = _evaluate(root->get_child(1));
        std::vector<std::string> v3 = _string_evalute(root->get_child(2));
        rt = lib_draw::draw_text(v1, v2, v3);
        
    } else if (name.compare("PARTLINE2") == 0) {
        vector<double> v1;
        vector< vector<double> > v2;
        vector< vector<string> > v3;
        size_t size = root->get_child().size();
        for (size_t i = 0; i < size; i++) {
            if (i == 0) {
                v1 = _evaluate(root->get_child(0));
            } else {
                vector<double> p1 = _evaluate(root->get_child((int)i));
                vector<string> p2 = _property_evalute(root->get_child((int)i + 1));
                v2.push_back(p1);
                v3.push_back(p2);
                i++;
            }
        }
        rt = lib_draw::part_line2(v1, v2, v3);
    }
    return rt;
}

// + -
std::vector<double> evaluator::_add_evalute(ast_node::ptr root) {
    std::vector<double> rt;
    std::vector<double> v1 = _evaluate(root->get_child(0));
    std::vector<double> v2 = _evaluate(root->get_child(1));
    string op = root->get_text();
    for (size_t i = 0; i < v1.size() && i < v2.size(); i++) {
         if (op.compare("+") == 0) rt.push_back(v1[i] + v2[i]);
         else rt.push_back(v1[i] - v2[i]);
     }
    return rt;
}

// * /
std::vector<double> evaluator::_mul_evalute(ast_node::ptr root) {
    std::vector<double> rt;
    std::vector<double> v1 = _evaluate(root->get_child(0));
    std::vector<double> v2 = _evaluate(root->get_child(1));
    string op = root->get_text();
    for (size_t i = 0; i < v1.size() && i < v2.size(); i++) {
        if (op.compare("*") == 0) rt.push_back(v1[i] * v2[i]);
        else rt.push_back(v1[i] / v2[i]);
    }
    return rt;
}

// = != <>
std::vector<double> evaluator::_equal_evalute(ast_node::ptr root) {
    std::vector<double> rt;
    std::vector<double> v1 = _evaluate(root->get_child(0));
    std::vector<double> v2 = _evaluate(root->get_child(1));
    string op = root->get_text();
    for (size_t i = 0; i < v1.size() && i < v2.size(); i++) {
        if (op.compare("=") == 0) rt.push_back(v1[i] == v2[i] ? 1 : 0);
        else rt.push_back(v1[i] != v2[i] ? 1 : 0);
    }
    return rt;
}

// & &&
std::vector<double> evaluator::_and_evalute(ast_node::ptr root) {
    std::vector<double> rt;
    std::vector<double> v1 = _evaluate(root->get_child(0));
    std::vector<double> v2 = _evaluate(root->get_child(1));
    for (size_t i = 0; i < v1.size() && i < v2.size(); i++) {
        rt.push_back(v1[i] && v2[i] ? 1 : 0);
    }
    return rt;
}

// | ||
std::vector<double> evaluator::_or_evalute(ast_node::ptr root) {
    std::vector<double> rt;
    std::vector<double> v1 = _evaluate(root->get_child(0));
    std::vector<double> v2 = _evaluate(root->get_child(1));
    for (size_t i = 0; i < v1.size() && i < v2.size(); i++) {
        rt.push_back(v1[i] || v2[i] ? 1 : 0);
    }
    return rt;
}

// > >= < <=
std::vector<double> evaluator::_rel_evalute(ast_node::ptr root) {
    std::vector<double> rt;
    std::vector<double> v1 = _evaluate(root->get_child(0));
    std::vector<double> v2 = _evaluate(root->get_child(1));
    string op = root->get_text();
    for (size_t i = 0; i < v1.size() && i < v2.size(); i++) {
        if (op.compare(">") == 0) rt.push_back(v1[i] > v2[i] ? 1 : 0);
        else if (op.compare(">=") == 0) rt.push_back(v1[i] >= v2[i] ? 1 : 0);
        else if (op.compare("<") == 0) rt.push_back(v1[i] < v2[i] ? 1 : 0);
        else rt.push_back(v1[i] <= v2[i] ? 1 : 0);
    }
    return rt;
}

// string
std::vector<std::string> evaluator::_string_evalute(ast_node::ptr root) {
    std::vector<string> rt;
    if (root->get_type() == ast_node_type::string_literal) {
        for (size_t i = 0; i < data.size(); i++) {
            rt.push_back(root->get_text());
        }
    }
    return rt;
}

// static value replace
std::vector<double> evaluator::_static_evalute(ast_node::ptr root) {
    std::vector<double> rt;
    if (root->get_type() == ast_node_type::static_literal) {
        string name = root->get_text();
        if (name.compare("DRAWNULL") || name.compare("NULL")) {
            for (size_t i = 0; i < data.size(); i++) {
                rt.push_back(draw_null);
            }
        }
    }
    return rt;
}

// propert string format
std::vector<std::string> evaluator::_property_evalute(ast_node::ptr root) {
    std::vector<string> rt;
    if (root->get_type() == ast_node_type::property_literal) {
        for (size_t i = 0; i < data.size(); i++) {
            rt.push_back(root->get_text());
        }
    }
    return rt;
}

std::vector<double> evaluator::_evaluate(ast_node::ptr root) {
    std::vector<double> rt;
    ast_node_type ty = root->get_type();
    
    if (ty == ast_node_type::digit_literal) {
        for (size_t i = 0; i < data.size(); i++) {
            rt.push_back(lib_math::string_2_double(root->get_text()));
        }
    } else if (ty == ast_node_type::static_literal) {
        rt = _static_evalute(root);
    } else if (ty == ast_node_type::fun_express) {
        rt = _call_function(root->get_text(), root);
    } else if (ty == ast_node_type::add_express) {
        rt = _add_evalute(root);
    } else if (ty == ast_node_type::mul_express) {
        rt = _mul_evalute(root);
    } else if (ty == ast_node_type::equal_express) {
        rt = _equal_evalute(root);
    } else if (ty == ast_node_type::and_express) {
        rt = _and_evalute(root);
    } else if (ty == ast_node_type::or_express) {
        rt = _or_evalute(root);
    } else if (ty == ast_node_type::rel_express) {
        rt = _rel_evalute(root);
    } else if (ty == ast_node_type::identifier) {
        string name = root->get_text();
        std::map< std::string, std::vector<double> >::iterator iter = variables.find(name);
        if (iter != variables.end()) {
            rt = iter->second;
        } else {
            std::cout << "Can not found var : " << name << std::endl;
        }
    }
    return rt;
}

evaluator::evaluator(std::vector< std::map<std::string, std::string> > dt) {
    tb = defined_table();
    data = dt;
}

result evaluator::evaluate(ast_node::ptr root) {
    std::map< std::string, std::vector<double> > value_1;
    map< string, vector< map<string, string> > > value_2;
    map< string, vector<string> > value_3;
    size_t idx = 0;
    for (ast_node::ptr node : root->get_child()) {
        ast_node::ptr statement = node->get_child(0);
        ast_node::ptr property = node->get_child(1);
        
        string key;
        if (statement->get_type() == ast_node_type::assignment || statement->get_type() == ast_node_type::return_assignment) {
            ast_node::ptr c1 = statement->get_child(0);
            ast_node::ptr c2 = statement->get_child(1);
            std::vector<double> val = _evaluate(c2);
            if (val.size()) {
                variables.insert({c1->get_text(), val});
                if (statement->get_type() == ast_node_type::return_assignment) {
                    key = c1->get_text();
                    value_1[key] = val;
                }
            }
        } else if (statement->get_type() == ast_node_type::fun_express) {
            string name = statement->get_text();
            if (tb.is_draw(name)) {
                vector< map<string, string> > val = _draw_function(name, statement);
                key = name + "_" + to_string(idx);
                if (val.size()) {
                    value_2[key] = val;
                }                
            } else {
                vector<double> val = _call_function(name, statement);
                key = name + "_" + to_string(idx);
                if (val.size()) {
                    value_1[key] = val;
                }
            }
        }
        
        if (key.length() && property != nullptr) {
            vector<string> pps;
            for (ast_node::ptr child : property->get_child()) {
                pps.push_back(child->get_text());
            }
            value_3[key] = pps;
        }
        
        idx ++;
    }
    return result(value_1, value_2, value_3);
}
