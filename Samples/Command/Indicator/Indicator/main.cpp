//
//  main.cpp
//  Indicator
//
//  Created by 许龙 on 2020/2/10.
//  Copyright © 2020 ldd. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "compiler.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...

    vector<map<string, string>> data;
    
    map<string, string> item1;
    item1.insert({"l", "354.40"});
    item1.insert({"o", "361.01"});
    item1.insert({"h", "383.17"});
    item1.insert({"c", "380.69"});
    data.push_back(item1);
    
    map<string, string> item2;
    item2.insert({"l", "354.40"});
    item2.insert({"o", "378.51"});
    item2.insert({"h", "383.17"});
    item2.insert({"c", "380.17"});
    data.push_back(item2);
    
    for (size_t i = 0; i < 26; i++) {
        map<string, string> item;
        item.insert({"l", "2013"});
        item.insert({"o", "2022"});
        item.insert({"h", "2025"});
        switch (i) {
            case 0: item.insert({"c", "451.6"}); break;
            case 1: item.insert({"c", "449.6"}); break;
            case 2: item.insert({"c", "458.9"}); break;
            case 3: item.insert({"c", "463.5"}); break;
            case 4: item.insert({"c", "458.0"}); break;
            case 5: item.insert({"c", "466.2"}); break;
            case 6: item.insert({"c", "480.2"}); break;
            case 7: item.insert({"c", "489.6"}); break;
            case 8: item.insert({"c", "499.7"}); break;
            case 9: item.insert({"c", "479.1"}); break;
            case 10: item.insert({"c", "464.0"}); break;
            case 11: item.insert({"c", "447.2"}); break;
            case 12: item.insert({"c", "404.9"}); break;
            case 13: item.insert({"c", "408.2"}); break;
            case 14: item.insert({"c", "415.4"}); break;
            case 15: item.insert({"c", "353.5"}); break;
            case 16: item.insert({"c", "357.3"}); break;
            case 17: item.insert({"c", "267.1"}); break;
            case 18: item.insert({"c", "244.9"}); break;
            case 19: item.insert({"c", "255.6"}); break;
            case 20: item.insert({"c", "283.5"}); break;
            case 21: item.insert({"c", "290.0"}); break;
            case 22: item.insert({"c", "253.7"}); break;
            case 23: item.insert({"c", "231.1"}); break;
            case 24: item.insert({"c", "229.0"}); break;
            case 25: item.insert({"c", "248.6"}); break;
            default: break;
        }
        data.push_back(item);
    }
    
    string tx = "\
    \
    //压力支撑1\
    MAL:=30;\
    FACTOR:=3;\
    REFCLOSE1:=REF(CLOSE,1);\
    TR:= MAX(MAX((HIGH-LOW),ABS(REFCLOSE1-HIGH)),ABS(REFCLOSE1-LOW));\
    ATR:= MA(TR,50);\
    CURRDN:=MA(CLOSE,MAL)+ ATR*FACTOR;\
    CURRUP:=MA(CLOSE,MAL)- ATR*FACTOR;\
    核心点位C:VALUEWHEN(CURRDN=LLV(CURRDN,14),CURRDN);\
    核心点位G:VALUEWHEN(CURRUP=HHV(CURRUP,14),CURRUP);\
    \
    TT:=核心点位C;\
    WW:=核心点位G;\
    \
    //压力支撑2\
    X:=5;\
    Y:=15;\
    STPL:=SMA(LOW,5,1);\
    STPH:=SMA(HIGH,5,1);\
    \
    KK:=LLV(STPL,X)+Y/10*ATR;\
    II:=HHV(STPH,X)-Y/10*ATR;\
    \
    //压力支撑3\
    MID :=  MA(CLOSE,20);\
    UDD:=MID + 2*STD(CLOSE,26);\
    LDD:=MID - 2*STD(CLOSE,26);\
    \
    //多空\
    CHH:=HHV(HIGH,10);\
    CLL:=LLV(LOW,10);\
    CHH1:=BARSLAST((CHH > REF(CHH,1)));\
    CLL1:=BARSLAST((CLL < REF(CLL,1)));\
    \
    DRAWTEXT(CROSS(CLL1,CHH1),L,'多');\
    DRAWTEXT(CROSS(CHH1,CLL1),H,'空');\
    \
    //压力位支撑位\
    G1:=MA(C,5);\
    D1:=MA(C,10);\
    NNH:=BARSLAST(H=HHV(H,7));\
    NNL:=BARSLAST(L=LLV(L,7));\
    NN:=IF(REF(G1,NNH)>REF(D1,NNH) AND NNH<=4,NNH,IF(REF(G1,NNL)<REF(D1,NNL) AND NNL<=4,NNL,5));\
    NB:=IF(ISLASTBAR AND NN>0,NN,5);\
    HH:=REF(H,NB)=HHV(H,6);\
    LL:=REF(L,NB)=LLV(L,6);\
    FG01:=BACKSET(HH,NB+1)>BACKSET(HH,NB);//只设置前面第6个\
    FD01:=BACKSET(LL,NB+1)>BACKSET(LL,NB);\
    FG02:=FG01=FD01 AND G1>D1;\
    FD02:=FG01=FD01 AND G1<D1;\
    TTTT:=BARSLAST(FD01);\
    FG0:=FG01 AND IF(FG02=1,H=HHV(H,BARSLAST(REF(FD01,1))+1),H=HHV(H,IF(BARSLAST(L=LLV(L,7))>=5,5,BARSLAST(FD01)))) AND FD02=0;\
    FD0:=FD01 AND IF(FD02=1,L=LLV(L,BARSLAST(REF(FG01,1))+1),L=LLV(L,IF(BARSLAST(H=HHV(L,7))>=5,5,BARSLAST(FG01))))  AND FG02=0;\
    GT:=BARSLAST(FG0);\
    DT:=BARSLAST(FD0);\
    LLLL:=DT=0 AND REF(DT,1)<GT AND L>REF(L,REF(DT,1)+1);\
    FG1:=BACKSET(REFX(GT,1)=0 AND GT<DT AND REFX(H,1)>=REF(H,GT),GT+1);\
    FD1:=BACKSET(REFX(DT,1)=0 AND DT<GT AND REFX(L,1)<=REF(L,DT),DT+1);\
    FG11:=IF(GT=0 AND REF(GT,1)<DT AND IF(REF(G1,BARSLAST(L=LLV(L,7)))>REF(D1,BARSLAST(L=LLV(L,7))),BARSLAST(L=LLV(L,7))<5,1) AND  H<REF(H,REF(GT,1)+1),1,0);\
    FD11:=IF(DT=0 AND REF(DT,1)<GT AND IF(REF(G1,BARSLAST(H=HHV(H,7)))<REF(D1,BARSLAST(H=HHV(H,7))),BARSLAST(H=HHV(H,7))<5,1) AND L>REF(L,REF(DT,1)+1),1,0);\
    //再次周期\
    GT1:=BARSLAST(FG11<>1 AND FG1<>1 AND FG0);\
    DT1:=BARSLAST(FD11<>1 AND FD1<>1 AND FD0);\
    FD2:=BACKSET(REFX(GT1,1)=0 AND DT1<3 AND GT1-DT1<4 AND REF(L,DT1)>LLV(L,GT1+5),DT1+1);\
    FG2A:=BACKSET(REFX(GT1,1)=0 AND DT1<3 AND GT1-DT1<4 AND REF(L,DT1)<=LLV(L,GT1+5) AND REF(H,GT1)>HHV(H,GT1+5),GT1+1);\
    FG2B:=IF(GT1=0 AND DT1<4 AND REF(GT1,1)-DT1<4 AND REF(L,DT1)<=LLV(L,REF(GT1,1)+6) AND H>HHV(H,REF(GT1,1)+6),1,0);\
    FG2:=BACKSET(REFX(DT1,1)=0 AND GT1<3 AND DT1-GT1<4 AND REF(H,GT1)<HHV(H,DT1+5),GT1+1);\
    FD2A:=BACKSET(REFX(DT1,1)=0 AND GT1<3 AND DT1-GT1<4 AND REF(H,GT1)>=HHV(L,DT1+5) AND REF(L,DT1)>LLV(L,DT1+5),DT1+1);\
    FD2B:=IF(DT1=0 AND GT1<4 AND REF(DT1,1)-GT1<4 AND REF(H,GT1)>=HHV(H,REF(DT1,1)+6) AND L>LLV(L,REF(DT1,1)+6),1,0);\
    TTTTTT:=H<REF(H,REF(GT1,1)+1) AND DT1<4;\
    HHHHHH:=REF(LLV(L,10),DT1);\
    FG21:=IF(GT1=0 AND DT1<4 AND H<=REF(H,REF(GT1,1)+1)  ,1,0);\
    FD21:=IF(DT1=0 AND GT1<4  AND L>=REF(L,REF(DT1,1)+1) ,1,0);\
    FD231:=BACKSET(REFX(GT1,1)=0 AND DT1>3 AND GT1>DT1 AND GT1-DT1<4 AND REFX(H,1)>REF(H,GT1) AND REF(L,DT1)>REF(LLV(L,10),DT1),DT1+1);\
    FG23:=BACKSET(REFX(GT1,1)=0 AND DT1>3 AND GT1>DT1 AND  GT1-DT1<4 AND REFX(H,1)>REF(H,GT1) AND (REF(H,GT1)<REF(HHV(H,13),GT1) OR REF(FD231,DT1)=0),GT1+1);\
    FG231:=BACKSET(REFX(DT1,1)=0 AND GT1>3  AND DT1>GT1 AND DT1-GT1<4 AND REFX(L,1)<REF(L,DT1) AND REF(H,GT1)<REF(HHV(H,10),GT1) ,GT1+1);\
    FD23:=BACKSET(REFX(DT1,1)=0 AND GT1>3  AND DT1>GT1 AND DT1-GT1<4 AND REFX(L,1)<REF(L,DT1) AND ( REF(L,DT1)>REF(LLV(L,13),DT1) OR REF(FG231,GT1)=0),DT1+1);\
    FDD23:=REF(H,GT1)<REF(HHV(H,10),GT1) OR REF(FD23,DT1)=0;\
    FD24:=BACKSET(REFX(GT1,1)=0 AND DT1>3 AND GT1>DT1 AND GT1-DT1<4 AND REFX(H,1)<HHV(H,GT1+3) AND REF(L,DT1)>LLV(L,DT1+5),DT1+1);\
    FG24:=BACKSET(REFX(DT1,1)=0 AND GT1>3  AND DT1>GT1 AND DT1-GT1<4 AND REFX(L,1)>LLV(L,DT1+3) AND REF(H,GT1)<HHV(H,GT1+5),GT1+1);\
    GT2:=BARSLAST(FG21<>1 AND FG23<>1 AND FG231<>1 AND FG24<>1   AND FG2<>1 AND FG2A<>1 AND FG2B<>1 AND GT1=0);\
    DT2:=BARSLAST(FD21<>1 AND FD23<>1 AND FD231<>1 AND FD24<>1  AND FD2<>1 AND FD2A<>1 AND FD2B<>1 AND DT1=0);\
    FG3:=BACKSET(REFX(GT2,1)=0 AND GT2<DT2 AND REFX(H,1)>=REF(H,GT2),GT2+1);\
    FD3:=BACKSET(REFX(DT2,1)=0 AND DT2<GT2 AND REFX(L,1)<=REF(L,DT2),DT2+1);\
    FG31:=IF(GT2=0 AND REF(GT2,1)<DT2 AND H<REF(H,REF(GT2,1)+1),1,0);\
    FD31:=IF(DT2=0 AND REF(DT2,1)<GT2 AND L>REF(L,REF(DT2,1)+1),1,0);\
    GT3:=BARSLAST(GT2=0 AND FG3<>1 AND FG31<>1 );\
    DT3:=BARSLAST(DT2=0 AND  FD3<>1 AND FD31<>1);\
    FG4:=BACKSET(REFX(GT3,1)=0 AND GT3<DT3 AND REFX(H,1)>=REF(H,GT3),GT3+1);\
    FD4:=BACKSET(REFX(DT3,1)=0 AND DT3<GT3 AND REFX(L,1)<=REF(L,DT3),DT3+1);\
    FG41:=IF(GT3=0 AND REF(GT3,1)<DT3 AND H<REF(H,REF(GT3,1)+1),1,0);\
    FD41:=IF(DT3=0 AND REF(DT3,1)<GT3 AND L>REF(L,REF(DT3,1)+1),1,0);\
    HHH:=GT3=0 AND FG31<>1 AND  FG3<>1;\
    LLL:=DT3=0 AND FD31<>1 AND  FD3<>1;\
    H11:=VALUEWHEN(HHH,H);\
    L1:=VALUEWHEN(LLL,L);\
    \
    HHH1:=VALUEWHEN(HHH,H);\
    LLL1:=VALUEWHEN(LLL,L);\
    H2:=VALUEWHEN(HHH,REF(HHH1,1));\
    L2:=VALUEWHEN(LLL,REF(LLL1,1));\
    \
    DRAWTEXT((CROSS(C,HHH1)&&C>TT&&C>KK&&C>UDD)||(HHH&&H2<HHH1&&H>TT&&H>KK&&H>UDD),H,'压力');\
    DRAWTEXT((CROSS(LLL1,C)&&C<WW&&C<II&&C<LDD)||(LLL&&L2>LLL1&&L<WW&&L<II&&L<LDD),L,'支撑');\
    ";
    
    
    compiler clr = compiler(data);
    clr.debug = true;
    result val = clr.compile(tx);
    
    return 0;
}
