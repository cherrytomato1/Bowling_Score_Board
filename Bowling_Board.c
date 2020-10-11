  1 #include<stdio.h>
  2 #include<stdlib.h>
  3 #include<time.h>
  4 typedef struct                  //구조체 사용
  5 {
  6         int p;                  //p : 플레이어 수
  7         int cp;                 //cp : 해당 플레이어(현재 투구중인 플레이어)
  8         int hit[3][10][4];      //각 투구당 점수를 정의하는 배열 ([3]은 투구 [10]은 프레임 [4]는 플레이어)
  9         int sum[10][4];         //프레임당 총합점수 ([10]은 프레임 [4]는 플레이어
 10         int pins;               //한번 투구후에 남은 핀수
 11         int frm;                //현재 프레임
 12         int thw;                //현재 투구
 13         int bns[10][4];         //보너스 판별용 배열(스트라이크나 스페어시 각각 값을 입력)
 14         char rnd;               //랜덤 플레이어 용 변수(랜덤을 실행할건지 안할건지 물어보아 그에 따른 값을 입력
 15 } score ;                       //구조체의 이름
 16 int input(int pins,char rnd,int cp)             //값 입력받기용 함수 (pins 투구후 남은 핀수,rnd 랜덤 사용 여부, cp 현재 플레이어)
 17 {
 18         int iScore;             //점수를 받을 변수
 19         printf("  ◆ 남은 핀 개수 : %d 개 \n\n",pins);           //남은핀의 개수를 알려주어 남은 핀보다 많이 입력하지 않게 해줌
 20         if(rnd=='y'&&cp!=0)                                     //랜덤 함수가 y이고 현재 플레이어가 첫번째 플레이어가 아닐때
 21         {
 22                 printf("  ◆ 컴퓨터 플레이어 투구 \n",pins);     //메세지 출력
 23                 getchar();                                      //enter를 입력해야 진행을 할 수있게 넣은 부분
 24                 iScore=rand()%(pins+1);                         //점수 값에 남은핀보다 적거나 같은 랜덤 변수를 넣음
 25         }
 26         else
 27         {
 28                 printf("  ◆ 점수를 입력하세요 \n",pins);                //메세지 출력
 29                 scanf("%d",&iScore);                                    //점수 값을 입력받음
 30                 getchar();                                              //입력 버퍼를 초기화 시켜줌
 31                 while(pins<iScore||iScore<0)                            //입력한 값이 0보다 작거나 남은 핀수보다 많을 때
 32                 {
 33                         printf("  ◆ 잘못된 값을 입력했습니다. \n  ◆ 남은 핀 개수 %d 개 \n\n",pins);     //잘못됨을 알림
 34                         scanf("%d",&iScore);                            //재입력받음
 35                         getchar();                                      //입력버퍼 초기화
 36                 }
 37         }
 38         return iScore;                                                  //입력받은 점수를 리턴
 39 }
 40 int play1(score *p1sc)                                                  //투구 실행 함수
 41 {
 42         printf("\n  ◆ 플레이어 %d, %d프레임 %d 번째 굴리기\n",p1sc->cp+1,p1sc->frm+1,p1sc->thw+1);      //몇번째플레이어인지, 몇번째 프레임인지 몇번째 투구인지 알림
 43         p1sc->hit[p1sc->thw][p1sc->frm][p1sc->cp]=input(p1sc->pins,p1sc->rnd,p1sc->cp);         //투구당 점수[현재 투구][현재프레임][현재플레이어]를 input(남은핀,랜덤여부,현재플레이어)로 받음.
 44         if(p1sc->hit[p1sc->thw][p1sc->frm][p1sc->cp]==p1sc->pins)               //투구 점수[현재투구][현재프레임][현재플레이어]가 남은 핀수와 같을 때 (남은 핀을 모두 쓰러뜨렸을때)
 45         {
 46                 if(p1sc->thw==0)                                        //현재 투구가 첫번째 투구일 때
 47                         p1sc->bns[p1sc->frm][p1sc->cp]+=2;              //보너스[현재프레임][현재플레이어]를 2(스트라이크 판정)로 설정
 48                 if(p1sc->thw==1)                                        //현재 투구가 두번째 투구일 때
 49                         p1sc->bns[p1sc->frm][p1sc->cp]+=1;              //보너스[현재프레임][현재플레이어]를 1(스페어 판정)로 설정
 50         }
 51         return 10-p1sc->hit[p1sc->thw][p1sc->frm][p1sc->cp];            //10-현재투구의 점수를 리턴(남은 핀 수)
 52 }
 53 int print(score *pr_sc)                                                 //출력 함수
 54 {
 55         int j,i,k,l;                                                    //반복문용 변수 j i k l
 56         for(i=0;i<50;i++)                                               //이전 출력을 지우기위한 반복문
 57                 printf("\n");
 58         for(k=0;k<pr_sc->p;k++)                                         //p(설정한 플레이어 수)만큼 반복
 59         {
 60                 if(k==0)                                                //첫번째 반복일 때
 61                 {
 62                         printf("┌────────────┬");                       //점수판 그림 출력을 위한 부분
 63                         for(l=0;l<9;l++)                                //9번반복
 64                                 printf("────────┬");
 65                         printf("────────────┐\n");
 66                         printf("│   프레임   │");
 67                         for(l=0;l<9;l++)                                //9번반복
 68                                 printf("    %d   │",l+1);               //프레임 수 출력
 69                         printf("      10    │\n");                      //마지막 프레임 출력
 70                         printf("└────────────┴");
 71                         for(l=0;l<9;l++)                                //9번 반복
 72                                 printf("────────┴");
 73                         printf("────────────┘\n");
 74                         printf("┌────────────┬");
 75                         for(l=0;l<9;l++)                                //9번 반복
 76                                 printf("────┬───┬");
 77                         printf("────┬───┬───┐\n");
 78                 }
 79                 printf("│ 플레이어 %d │ ",k+1);                         //플레이어 수 출력
 80                                                                 //각 투구 별 점수 출력 부분
 81                 for(j=0;j<10;j++)                                       //10번반복(프레임 수 만큼)
 82                 {
 83                         printf(" ");                                    //칸수 맞추기
 84                         for(i=0;i<2;i++)                                //2번 반복(투구 수 만큼)
 85                         {
 86                                 if(pr_sc->hit[i][j][k]==-1)             //-1로 초기화 된 상태(초기화 된 이후 다른 값이 들어가지 않은 상태
 87                                         printf(" ");                    //공백 출력
 88                                 else if(pr_sc->hit[i][j][k]==10)        //해당 투구 점수가 10일때 (스트라이크)
 89                                         printf("X");                    //스트라이크 출력
 90                                 else if(pr_sc->hit[i][j][k]==0)         //해당 투구 점수가 0점일때
 91                                         printf("-");                    //0점 표시 출력
 92                                 else if(i==1&&pr_sc->hit[0][j][k]+pr_sc->hit[1][j][k]==10)      //두번째 투구이고,첫번째 투구와 두번째 투구를 합쳐서 10점일때 (스페어)
 93                                         printf("/");                    //스페어 출력
 94                                 else                                    //특별한 경우가 아닐 때
 95                                         printf("%d",pr_sc->hit[i][j][k]);       //점수를 숫자로 출력한다.
 96                                 printf(" │ ");                          //칸 나눔
 97                         }
 98                         if(j==9)                                        //10번째 프레임의 보너스 투구를 위한 부분
 99                         {                                               //출력방식은 위와 같음
100                                 if(pr_sc->hit[i][j][k]==-1)             //초기화 된 상태에서 다른 값이 들어가지 않았을 때
101                                         printf(" ");
102                                 else if(pr_sc->hit[i][j][k]==10)        //스트라이크
103                                         printf("X");
104                                 else if(pr_sc->hit[i][j][k]==0)         //0점
105                                         printf("-");
106                                 else if(i==1&&pr_sc->hit[0][j][k]+pr_sc->hit[1][j][k]==10)      //스페어
107                                         printf("/");
108                                 else
109                                         printf("%d",pr_sc->hit[i][j][k]);       //점수출력
110                                 printf(" │ ");                          //칸 나눔
111                         }
112                 }
113                 printf("\n│            │   ");                          //공백 출력
114                                                                 //총합 점수 출력 부분
115                 for(j=0;j<10;j++)                                       //10번 반복 (프레임 수 만큼)
116                 {
117                         if(j==9)                                //10프레임시에 투구가 3번이기에 추가 공백
118                                 printf("    ");
119                         if(pr_sc->sum[j][k]==-1)        //-1로 초기화된 상태일 때(초기화 후 점수가 입력되지 않았을 때)
120                                 printf("    ");         //공백 출력
121                         else
122                                 printf(" %3d",pr_sc->sum[j][k]);        //세자릿수에 맞추어 총합점수[j][k]를 출력
123                         printf(" │   ");                        //칸 나누기
124                 }
125                 printf("\n");
126                 if(k<pr_sc->p-1)                                //반복문 변수 k가 설정한 플레이어수-1 보다 작을 때
127                 {
128                         printf("├────────────┼");               //밑칸과 이어지는 표 출력
129                         for(l=0;l<9;l++)
130                                 printf("────┬───┼");
131                         printf("────┬───┬───┤\n");
132                 }
133                 else                                            //아닐경우 ( k>=설정한 플레이어수)
134                 {
135                         printf("└────────────┴");               //닫혀있는 표 출력
136                         for(l=0;l<9;l++)
137                                 printf("────────┴");
138                         printf("────────────┘\n");
139                 }
140         }
141 }
142 int add(score *ad_sc)                                   //점수계산함수
143 {
144         if(ad_sc->thw==0)                                               //투구수가 0(첫번째 투구)일 때  총합점수에 1을 더함(초기화를 -1로 했기 때문)
145                 ad_sc->sum[ad_sc->frm][ad_sc->cp]++;
146         if(ad_sc->bns[ad_sc->frm-1][ad_sc->cp]==0)                      //보너스[현재프레임 -1][현재플레이어]가 0일 때(이전 프레임에 스트라이크나 스페어가 없을 때)
147         {
148                 if(ad_sc->frm!=0&&ad_sc->thw==0)                                //첫번째 프레임이 아닐때 그리고 첫번째 투구일 때
149                         ad_sc->sum[ad_sc->frm][ad_sc->cp]+=ad_sc->sum[ad_sc->frm-1][ad_sc->cp];         //이전프레임의 점수를 현재프레임의 점수에 더함.
150         }
151         else if(ad_sc->bns[ad_sc->frm-1][ad_sc->cp]==1&&ad_sc->thw==0)                  //전 프레임에서 스페어 판정이 나고 투구수가 0일 때(첫번째 투구)
152         {
153                 ad_sc->sum[ad_sc->frm-1][ad_sc->cp]+=ad_sc->hit[0][ad_sc->frm][ad_sc->cp];      //현재 프레임의 첫 투구 점수를 이전 프레임점수 총합 점수에 더함
154                 ad_sc->sum[ad_sc->frm][ad_sc->cp]+=ad_sc->sum[ad_sc->frm-1][ad_sc->cp];         //이전 프레임의 총합점수를 현재프레임 총합점수에 더함.
155         }
156
157                                                         //스트라이크 부분
158         else if(ad_sc->bns[ad_sc->frm-1][ad_sc->cp]==2)                                 //보너스[현재프레임-1][현재플레이어]가 2일때(이전 프레임에서 스트라이크일때)
159         {
160                 if(ad_sc->thw==0)                                                       //첫번째 투구일 때
161                         ad_sc->sum[ad_sc->frm][ad_sc->cp]+=ad_sc->sum[ad_sc->frm-1][ad_sc->cp];         //이전 프레임의 총합 점수를 현재 프레임 총합점수에 더한다.
162                 if(ad_sc->thw!=2)                                                       //세번째 투구가 아닐때(세번쨰 투구는 10프레임 전용)
163                 {
164                         ad_sc->sum[ad_sc->frm-1][ad_sc->cp]+=ad_sc->hit[ad_sc->thw][ad_sc->frm][ad_sc->cp];     //이전 프레임의 총합점수에 현재 투구의 점수를 더함
165                         ad_sc->sum[ad_sc->frm][ad_sc->cp]+=ad_sc->hit[ad_sc->thw][ad_sc->frm][ad_sc->cp];       //현재 프레임의 총합점수에 현주 투구의 점수를 더함(2번째 더해짐)
166                 }
167                                                                         //더블 스트라이크 부분
168                 if(ad_sc->bns[ad_sc->frm-2][ad_sc->cp]==2)                              //2번째 전의 프레임에서 스트라이크가 나왔을 때
169                 {
170                         if(ad_sc->thw==0)                                               //첫번째 투구일 때
171                         {
172                                 ad_sc->sum[ad_sc->frm-2][ad_sc->cp]+=ad_sc->hit[ad_sc->thw][ad_sc->frm][ad_sc->cp];     //2번째 전의 프레임 총합점수에 현재 프레임의 현재 투구의 점수를 더함
173                                 if(ad_sc->thw!=2)                                       //세번째 투구가 아닐 때
174                                 {
175                                         ad_sc->sum[ad_sc->frm-1][ad_sc->cp]+=ad_sc->hit[ad_sc->thw][ad_sc->frm][ad_sc->cp];     //이전 프레임의 총합점수에 현재 투구의 점수를 더함(2번째)
176                                         ad_sc->sum[ad_sc->frm][ad_sc->cp]+=ad_sc->hit[ad_sc->thw][ad_sc->frm][ad_sc->cp];       //현재 프레임의 총합점수에 현재 투구의 점수를 더함(3번째)
177                                 }
178                         }
179                 }
180         }
181         ad_sc->sum[ad_sc->frm][ad_sc->cp]+=10-ad_sc->pins;                              //프레임별 총합점수에 10-남은핀의 개수를 더함(현재 투구의 점수를 더함)
182 }
183 int main()
184 {
185         score sc;                               //구조체 정의
186         int i,j,k,result[4][2];                 //반복문용 변수 i j k, 결과값 출력 및 순위 계산을 위한 변수 result[플레이어][0= 점수,1=플레이어 번호]
187         for(i=0;i<50;i++)                       //이전 출력 삭제 반복문
188                 printf("\n");
189         printf("\n  ◆ 게임을 시작합니다\n\n  ◆ 플레이어 숫자를 입력해주세요(최대 4명)\n\n\n");          //프로그램 안내
190         scanf("%d",&sc.p);                      //플레이어 수를 입력받음
191         getchar();                              //입력버퍼 제거
192         while(sc.p<1||sc.p>4)
193         {
194                 for(i=0;i<50;i++)               //이전출력삭제
195                         printf("\n");
196                 printf("\n  ◆ 게임을 시작합니다\n\n  ◆ 플레이어 숫자를 입력해주세요(최대 4명)\n");
197                 printf("  ◆ 잘못된 플레이어 숫자 입니다(1~4)\n\n");             //잘못됨을 알림
198                 scanf("%d",&sc.p);              //재 입력받음
199                 getchar();                      //입력버퍼삭제
200         }
201         if(sc.p>1)                              //플레이어 수가 1보다 클때(2명 이상일 때)
202         {
203                 for(i=0;i<50;i++)               //이전 출력삭제
204                         printf("\n");
205                 printf("\n  ◆ 컴퓨터 플레이어를 설정하시겠습니까? (y,n)\n\n\n");
206                 scanf("%c",&sc.rnd);            //rnd에 y또는 n을 입력받는다(rnd는 랜덤 플레이어 확인변수)
207                 getchar();                      //입력버퍼제거
208                 while(sc.rnd!='y'&&sc.rnd!='n') //rnd가 y가 아니고 n도 아닐 때
209                 {
210                         printf("  ◆ y 또는 n을 입력해주세요.\n\n\n");   //잘못됨을 알림
211                         scanf("%c",&sc.rnd);                            //재 입력받기
212                         getchar();              //입력버퍼제거
213                 }
214                 if(sc.rnd=='y')                 //rnd에 y를 입력했을 때
215                         srand(time(NULL));      //srand 함수를 사용
216         }
217
218         for(i=0;i<10;i++)                       //변수 및 배열 초기화 (i = 프레임수)
219         {
220                 for(k=0;k<4;k++)                //플레이어 수
221                 {
222                         for(j=0;j<3;j++)        //투구 수
223                                 sc.hit[j][i][k]=-1;     //진행된 정도를 알기위해 -1로 초기화한다 (-1인 부분은 아직 실행되지 않은 부분으로 판별
224                         sc.sum[i][k]=-1;        //-1로 초기화
225                         sc.bns[i][k]=0;
226                 }
227         }
228         print(&sc);                             //게임판 출력 함수 실행
229         for(sc.frm=0;sc.frm<9;sc.frm++)         //9회 프레임 반복(10번째 프레임은 분리)
230         {
231                 for(sc.cp=0;sc.cp<sc.p;sc.cp++) //설정한 플레이어 수 만큼 반복
232                 {
233                         sc.pins=10;                             //매 프레임마다 남은 핀수 갱신
234                         for(sc.thw=0;sc.thw<2&&sc.pins!=0;sc.thw++)     //남은핀이 0개가 아닐때 투구 진행
235                         {
236                                 sc.pins=play1(&sc);                     //함수에 구조체의 주솟값을 보내주며 실행
237                                 add(&sc);                               //점수 계산함수 실행
238                                 print(&sc);                             //출력함수 실행
239                         }
240                 }
241         }
242                                                 //10프레임 부분
243         for(sc.cp=0;sc.cp<sc.p;sc.cp++)                         //현재 플레이어 수만큼 반복
244         {
245                 sc.pins=10;                                     //남은 핀수 초기화
246                 for(sc.thw=0;sc.thw<3;sc.thw++)                 //투구를 3번 반복(10프레임이기 때문에)
247                 {
248                         sc.pins=play1(&sc);                     //함수들 실행
249                         add(&sc);
250                         print(&sc);
251                         if(sc.pins==0)                          //남은핀수가 0개가 되면 10개로 만든다(10프레임은 0개가 되면 보너스를 준다)
252                                 sc.pins=10;
253                         if(sc.thw==1&&sc.bns[9][sc.cp]==0)      //2번째 투구이고 이번 프레임에서 보너스를 얻지 못했을 때
254                                 break;                          //반복 종료(3번째 투구 생략)
255                 }
256         }
257
258         for(i=0;i<sc.p;i++)                                     //설정된 플레이어 수만큼 반복
259         {
260                 result[i][0]=sc.sum[9][i];                      //result[i][0]을 총합점수로 대입 (각플레이어의 총합점수를 대입)
261                 result[i][1]=i;                                 //result[i][1]에는 각플레이어의 플레이어 번호를 넣는다(정렬할 때 구분하기 위함)
262         }
263         printf("          ◆ 게임이 종료 되었습니다. 계속하려면 enter 입력\n\n");        //게임 끝 안내
264         getchar();                                              //입력버퍼제거
265         print(&sc);                                             //점수판 표시
266         printf("          ◆ 게임 결과\n\n");                    //게임결과 출력
267         for(i=0;i<sc.p;i++)                                     //플레이어 수만큼 반복
268                 printf("       ●  플레이어 %d    %d점\n",i+1,result[i][0]);             //플레이어의 번호와 그 점수를 출력
269
270         for(i=0;i<sc.p;i++)                             //설정한 플레이어 수만큼 반복
271         {
272                 for(j=i+1;j<sc.p;j++)                   //j가 i+1부터 설정한 플레이어 수만큼 반복
273                 {                                       //역버블정렬을 사용해 점수정렬
274                         if(result[i][0]<result[j][0])           //result[i][0]와 result[j][0]를 비교해서 result[j][0]가 더 클경우
275                         {
276                                 k=result[i][0];         //result[i][0]를 k에 임시저장
277                                 result[i][0]=result[j][0];      //result[i][0]에 result[j]를 대입
278                                 result[j][0]=k;         //k에 저장된 값을 result[j][0]에 대입
279                                 k=result[i][1];         //result[i][1]를 k에 임시저장
280                                 result[i][1]=result[j][1];      //result[i][1]에 result[j]를 대입
281                                 result[j][1]=k;         //k에 저장된 값을 result[j][1]에 대입
282                         }
283                 }
284         }
285         printf("\n          ◆ 게임 순위\n\n");          //순위 출력
286         for(i=0;i<sc.p;i++)                             //설정한 플레이어 수만큼반복
287                 printf("    ●  %d위  플레이어 %d    %d점\n",i+1,result[i][1]+1,result[i][0]); //플레이어 순위, 플레이어 번호, 그 플레이어의 점수를 출력.
288         return 0;
289 }