#include "healthDataReport.h"

//每个报告的数量
char reportLength[25] = {20,10,14,18,16,17,5,8,10,5,10,5,6,10,7,8,11,15,18,15,5,5,15,24,16};
//    心血管1                          
char *healthData1[20] = {
"01.左心室喷血阻抗         [1.551-2.875]",            
"02.主动脉排空系数         [1.551-4.475]",
"03.血管弹性               [10.73-216.3]",
"04.血液粘度               [6.012-6.892]",
"05.心肌血液供耗量         [0.983-1.265]",
"06.血管阻力               [0.831-1.248]",
"07.胆固醇结晶             [1.263-2.671]",
"08.心脏指数               [0.316-0.401]",
"09.每搏心搏出量           [1.643-2.070]",
"10.血管顺应度             [4.073-4.579]",
"11.血脂                   [0.643-1.078]",
"12.冠状动脉弹性           [0.731-1.307]",
"13.冠状动脉灌注压         [13.01-17.29]",
"14.血管总弹性指数         [0.710-1.109]",
"15.冠动脉供血指数         [7.880-10.09]",
"16.心肌耗氧量             [5.071-5.597]",
"17.左心室有效泵力         [1.156-4.596]",
"18.心肌血液需量           [2.017-5.597]",
"19.心肌血液灌注量         [4.131-4.562]",
"20.心搏指数               [1.560-2.960]",
};

// .    心血管2
char *healthData2[10] = {
"01.肺动脉压               [15.00-22.00]",
"02.肺血管助力             [100.0-200.0]",
"03.肺动脉楔压             [6.000-12.00]",
"04.左室喷血阻抗           [160.0-220.0]",
"05.总周阻                 [100.0-140.0]",
"06.血管弹性系数           [100.0-130.0]",
"07.心动脉排空系数         [0.350-0.550]",
"08.主动脉排空系数         [0.220-0.264]",
"09.冠状动脉灌注压         [50.00-70.00]",
"10.心肌血液需要量         [200.0-400.0]",
};

//�.竽�
char *healthData3[14] = {
"01.情绪怒指数             [0.202-0.991]",
"02.脑神经功能状况         [0.253-0.659]",
"03.脑动脉硬化指数         [0.103-0.642]",
"04.脑组织供血状况         [1.370-2.810]",
"05.大脑功能指数           [0.689-0.987]",
"06.小脑功能指数           [0.433-0.796]",
"07.情绪惊指数             [0.432-0.826]",
"08.情绪恐指数             [0.202-0.991]",
"09.情绪喜指数             [0.432-0.826]",
"10.情绪忧指数             [0.433-0.796]",
"11.情绪悲指数             [0.713-0.992]",
"12.情绪思指数             [116.3-220.6]",
"13.记忆指数（ZS）         [0.407-0.749]",
"14.情绪指数               [0.168-0.992]",
};

// .    肺部
char *healthData4[18] = {
"01.非总量指数             [2.163-7.321]",
"02.残气量指数             [0.824-1.942]",
"03.潮气量                 [5.327-70.19]",
"04.气道阻力指数           [0.717-1.512]",
"05.血氧指数               [0.842-1.858]",
"06.肺泡通气量             [1.449-2.246]",
"07.肺动脉弹性             [2.124-4.158]",
"08.补吸气量               [0.218-0.953]",
"09.用力肺活量指数         [0.346-0.501]",
"10.用力通气量指数         [1.471-6.879]",
"11.肺血管阻力指数         [2.967-3.528]",
"12.呼吸肌力指数           [2.845-4.017]",
"13.肺容量                 [1.053-3.230]",
"14.补呼气量               [1.903-2.012]",
"15.时间肺活量             [4.301-6.782]",
"16.肺总量指数             [3.210-6.854]",
"17.动脉血氧量指数         [2.204-2.819]",
"18.肺动脉压指数           [3.348-4.529]",
};

// .    肝胆
char *healthData5[16] = {
"01.肝胆脂肪含量指数       [0.097-0.419]",
"02.蛋白质合成指数         [3.572-6.483]",
"03.胆固醇合成指数         [3.241-9.814]",
"04.脂肪酸分解指数         [4.111-18.74]",
"05.胆汁排泄指数           [6.818-16.74]",
"06.脂肪的释放指数         [2.213-2.717]",
"07.胆汁分泌指数           [0.432-0.826]",
"08.肝解毒功能指数         [0.202-0.991]",
"09.分泌胆汁指数           [3.142-7.849]",
"10.能量生产功能           [3.712-6.981]",
"11.脂蛋白合成指数         [2.946-3.515]",
"12.酒精代谢指数           [0.713-0.992]",
"13.肝糖原分解指数         [1.023-3.230]",
"14.肝糖原合成指数         [1.471-6.079]",
"15.脂肪的合成指数         [3.342-9.461]",
"16.蛋白质代谢指数         [1.734-2.621]",
};

// .    妇科
char *healthData6[17] = {
"01.黄体酮                 [6.818-16.74]",
"02.泌乳素                 [3.142-7.849]",
"03.促性腺激素             [4.886-8.931]",
"04.磁性激素               [3.296-8.840]",
"05.孕激素                 [0.142-0.495]",
"06.外阴炎系数             [2.967-3.528]",
"07.尿道炎系数             [2.163-7.321]",
"08.阴道炎系数             [2.204-2.819]",
"09.宫颈炎系数             [2.845-4.017]",
"10.宫颈糜烂系数           [2.954-5.543]",
"11.宫颈囊肿系数           [2.412-2.974]",
"12.宫颈息肉系数           [2.374-3.709]",
"13.附件炎系数             [2.301-4.782]",
"14.盆腔炎系数             [1.348-3.529]",
"15.输卵管炎系数           [2.560-4.960]",
"16.子宫肌瘤系数           [1.017-3.579]",
"17.卵巢囊肿系数           [2.012-4.892]",
};

// .     乳腺
char *healthData7[5] = {
"01.乳腺纤维瘤系数         [0.433-0.796]",
"02.慢性乳腺炎系数         [0.432-0.826]",
"03.乳腺增生系数           [0.202-0.991]",
"04.急性乳腺炎系数         [0.713-0.992]",
"05.内分泌失调系数         [1.684-4.472]",
};

// .   内分泌
char *healthData8[8] = {
"01.松果体分泌指数         [3.210-6.854]",
"02.胰岛分泌指数           [2.019-4.721]",
"03.腺分泌指数             [2.967-3.528]",
"04.体分泌指数             [2.163-7.321]",
"05.性腺分泌指数           [2.204-2.819]",
"06.甲状旁腺分泌值         [2.845-4.017]",
"07.甲状腺分泌指数         [2.954-5.543]",
"08.肾上腺分泌指数         [2.412-2.974]"
};

//�.缡�
char *healthData9[10] = {
"01.颈椎钙化度             [0.421-0.490]",
"02.骨质增生系数           [2.954-5.543]",
"03.腰椎钙化度             [2.019-4.721]",
"04.风湿系数               [4.023-11.62]",
"05.颈部肌肉粘连度         [4.425-7.872]",
"06.腰部肌肉粘连度         [2.142-4.862]",
"07.肩部肌肉粘连度         [6.462-9.753]",
"08.韧带陈旧度             [3.684-5.472]",
"09.四肢循环受限性         [2.638-5.712]",
"10.骨质疏松系数           [4.326-7.531]",
};

// .    骨骼
char *healthData10[5] = {
"01.骨质增生度             [0.433-0.796]",
"02.骨质疏松度             [0.124-0.453]",
"03.骨密度                 [0.046-0.167]",
"04.钙流失量               [0.209-0.751]",
"05.破骨细胞系数           [86.73-180.9]",
};

// .   男科
char *healthData11[10] = {
"01.前列腺增生度           [1.023-3.230]",
"02.前列腺炎症             [2.213-2.717]",
"03.葡萄球菌感染值         [1.471-6.079]",
"04.前列腺分泌值           [0.630-1.712]",
"05.睾丸酮                 [3.342-9.461]",
"06.性腺激素               [3.241-9.814]",
"07.男性荷尔蒙             [4.111-18.74]",
"08.促性腺激素             [1.124-2.453]",
"09.前列腺钙化度           [0.421-0.890]",
"10.勃起传到素             [3.342-6.461]",
};

// .  肾脏
char *healthData12[5] = {
"01.肌苷指数               [2.213-5.717]",
"02.尿肝原指数             [2.762-5.424]",
"03.尿酸指数               [1.435-1.987]",
"04.尿素氮指数             [4.725-8.631]",
"05.尿蛋白指数             [1.571-4.079]",
};

// .   肥胖
char *healthData13[6] = {
"01.内脏肥胖指数           [0.346-0.401]",
"02.皮下肥胖指数           [1.449-2.246]",
"03.药源性肥胖指数         [0.097-0.419]",
"04.获得性肥胖指数         [0.202-0.907]",
"05.体质性肥胖指数         [3.241-9.814]",
"06.垂体性肥胖指数         [3.712-6.981]",
};

// .  胃肠
char *healthData14[10] = {
"01.胃节律絮乱系数         [0.124-0.453]",
"02.胃泌素系数             [4.326-7.531]",
"03.胃动力系数             [0.433-0.796]",
"04.肠动力系数             [0.046-0.167]",
"05.胃动素分泌系数         [0.209-0.751]",
"06.小肠吸收功能系数       [1.173-2.297]",
"07.胃酶分泌系数           [0.313-0.713]",
"08.胃吸收功能系数         [34.36-35.64]",
"09.小肠蠕动功能系数       [59.89-65.23]",
"10.胃蠕动功能系数         [0.346-2.167]",
};

// .   胰腺
char *healthData15[7] = {
"01.胰高血糖素             [2.214-2.819]",
"02.尿糖系数               [6.420-11.39]",
"03.胰岛素分泌系数         [2.946-3.515]",
"04.胰岛细胞指数           [1.824-2.942]",
"05.血糖系数               [2.142-3.495]",
"06.胰腺为分泌系数         [1.326-2.142]",
"07.胰多肽                 [2.143-3.989]",
};

// .   免疫
char *healthData16[8] = {
"01.胸腺免疫力             [58.42-61.21]",
"02.骨髓指数               [0.146-3.218]",
"03.脾脏指数               [34.36-35.64]",
"04.扁桃体免疫值           [0.124-0.453]",
"05.粘膜内免疫值           [4.111-18.74]",
"06.呼吸道免疫值           [3.241-9.814]",
"07.消化道免疫值           [0.638-1.712]",
"08.淋巴结免疫值           [133.4-140.4]",
};

// .   美容
char *healthData17[11] = {
"01.皮肤油脂指数           [14.47-21.34]",
"02.自由基指数             [0.124-3.453]",
"03.皮户角质指数           [0.842-1.858]",
"04.黑色数指数             [0.346-0.501]",
"05.皮肤弹性指数           [0.717-1.512]",
"06.红血丝指数             [1.824-1.942]",
"07.胶原蛋白指数           [1.471-6.079]",
"08.皮肤免疫指数           [1.053-3.230]",
"09.毛细血管扩张度         [5.327-70.19]",
"10.皮肤水质指数           [0.218-0.953]",
"11.皮肤水分流失量         [2.124-4.158]",
};

// .   毒素
char *healthData18[15] = {
"01.烟油尼古丁值           [0.124-0.453]",
"02.农药残留毒值           [0.013-0.313]",
"03.电磁波辐射值           [0.046-0.167]",
"04.刺激性饮料值           [0.209-0.751]",
"05.有色金属值             [86.73-180.9]",
"06.油漆指数               [0.710-4.109]",
"07.紫外线指数             [0.407-0.749]",
"08.化妆品指数             [0.168-0.992]",
"09.洗涤用品指数           [0.689-0.987]",
"10.污水指数               [1.019-3.721]",
"11.重金属指数             [1.142-5.862]",
"12.食物添加剂指数         [2.462-5.753]",
"13.汽车尾气指数           [1.425-5.872]",
"14.排放毒气指数           [1.954-4.543]",
"15.食物防腐剂值           [122.9-213.8]",
};


// .   过敏1
char *healthData19[18] = {
"01.注射剂过敏指数         [2.374-3.709]",
"02.毒气过敏指数           [2.301-4.782]",
"03.异体蛋白过敏           [1.348-3.572]",
"04.柳絮过敏指数           [2.569-4.960]",
"05.抗菌数过敏指数         [1.017-3.597]",
"06.化纤用品过敏           [2.012-4.892]",
"07.细菌过敏指数           [1.012-2.291]",
"08.酒精过敏指数           [0.710-4.109]",
"09.紫外线过敏指数         [1.388-2.049]",
"10.花粉过敏指数           [0.731-3.389]",
"11.药物过敏指数           [2.093-4.012]",
"12.油漆过敏指数           [0.831-3.248]",
"13.粉尘过敏指数           [2.073-4.579]",
"14.汽车尾气过敏           [0.131-4.562]",
"15.辐射性过敏             [0.263-1.671]",
"16.煤气过敏指数           [2.483-4.256]",
"17.冷空气过敏指数         [1.735-2.396]",
"18.油烟过敏指数           [1.316-4.401]",
};

// .   过敏2
char *healthData20[15] = {
"01.鱼虾过敏指数           [3.012-7.291]",
"02.禽蛋过敏指数           [1.511-2.875]",
"03.精神紧张过敏           [5.017-5.597]",
"04.动物脂肪过敏           [0.407-0.749]",
"05.是有过敏指数           [0.109-0.351]",
"06.异种血清过敏           [1.560-2.960]",
"07.香精过敏指数           [0.253-0.659]",
"08.霉菌过敏指数           [0.103-0.642]",
"09.电力辐射过敏           [0.346-0.401]",
"10.微生物感染             [0.689-0.907]",
"11.海鲜过敏指数           [0.433-0.796]",
"12.动物绒毛过敏           [0.432-0.826]",
"13.金属饰品过敏           [0.168-0.992]",
"14.毒品过敏指数           [2.688-8.090]",
"15.牛奶过敏指数           [0.442-0.817]",
};                      

// .   多动症
char *healthData21[5] = { 
"01.锌吸收指数             [0.433-0.796]",
"02.铁吸收指数             [0.432-0.826]",
"03.一氧羟苯乙醇           [116.3-220.6]",
"04.GE类神经递质           [0.713-0.992]",
"05.香草酸                 [0.202-0.991]",
};                        

// .    生长
char *healthData22[5] = {
"01.生长潜能               [0.433-0.796]",
"02.生长线                 [0.432-0.826]",
"03.短骨生长状态           [0.202-0.991]",
"04.长骨愈合状态           [0.713-0.992]",
"05.骨骼钙化程度           [116.3-220.6]",
};                        

// .   体质
char *healthData23[15] = {
"01.自由基指数             [59.84-65.23]",
"02.脑力                   [58.71-63.21]",
"03.酸碱度                 [3.156-3.694]",
"04.缺水                   [33.96-37.64]",
"05.营养状况指数           [2.638-5.712]",
"06.反应力                 [59.78-65.42]",
"07.协调性指数             [0.710-4.109]",
"08.柔韧性指数             [4.326-4.531]",
"09.灵敏度指数             [2.954-5.543]",
"10.缺氧                   [2.688-8.090]",
"11.疾病抵抗力值           [2.019-4.721]",
"12.判断能力指数           [4.023-11.62]",
"13.平衡性指数             [133.6-141.4]",
"14.体质指数               [0.421-0.490]",
"15.新陈代谢系数           [3.684-5.472]",
};

// .   维生素
char *healthData24[24] = {
"01.维生素K                [0.717-1.486]",
"02.维生素E                [4.826-6.013]",
"03.维生素B6               [2.124-4.192]",
"04.维生素B2               [1.549-2.213]",
"05.维生素B15              [6.428-21.39]",
"06.维生素B12              [0.326-1.142]",
"07.维生素B17              [2.432-4.652]",
"08.叶酸                   [5.327-7.109]",
"09.泛酸                   [1.143-2.904]",
"10.维生素C                [0.824-1.942]",
"11.维生素B1               [4.543-5.023]",
"12.维生素A                [0.381-0.475]",
"13.维生素D3               [0.713-0.992]",
"14.维生素B16              [1.148-2.032]",
"15.赖氨酸                 [0.253-0.669]",
"16.色氨酸                 [2.374-3.709]",
"17.苯丙氨酸               [0.731-1.307]",
"18.蛋氨酸                 [0.432-0.826]",
"19.苏氨酸                 [0.422-0.817]",
"20.异亮氨酸               [1.831-3.248]",
"21.亮氨酸                 [2.073-4.579]",
"22.缬氨酸                 [2.012-4.892]",
"23.组氨酸                 [2.903-4.012]",
"24.精氨酸                 [0.710-1.209]",
};

// .    元素
char *healthData25[16] = {
"01.钙                     [7.019-3.721]",
"02.铁                     [0.689-0.987]",
"03.锌                     [1.137-2.401]",
"04.硒                     [2.462-5.753]",
"05.铜                     [1.954-4.543]",
"06.锰                     [0.097-0.479]",
"07.钒                     [122.9-2.318]",
"08.汞                     [0.407-0.749]",
"09.镁                     [1.421-5.490]",
"10.钾                     [1.023-7.627]",
"11.氟                     [1.425-5.872]",
"12.碘                     [1.142-5.862]",
"13.锂                     [1.604-4.472]",
"14.锶                     [0.630-1.712]",
"15.铅                     [1.124-3.453]",
"16.镍                     [0.160-0.992]",
};                   
