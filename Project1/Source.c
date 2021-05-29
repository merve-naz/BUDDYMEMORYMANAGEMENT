#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct node* head = NULL;
struct  INTERNAL* abas = NULL;
struct node {
	char durum[20];
	int MB;
	struct node* ptr;
};
struct  INTERNAL {
	char durum[20];

	int frag;
	struct INTERNAL* ptr1;
};
void yazdýr() {
	struct node* yr = head;
	struct INTERNAL* tr = abas;
	int i = 1, t = -1;
	if (head == NULL) {
		printf("dizi boþ");
		return;
	}

	else {
		while (yr != NULL) {
			printf("Block %d :%s - %d ", i, yr->durum, yr->MB);
			if (t == strcmp(yr->durum, "free")) {
				printf("(INTERNAL FRAGMENTATION: %d)", tr->frag);
				tr = tr->ptr1;
			}

			yr = yr->ptr;
			i++;
			printf("\n");
		}
	}
}
void main() {

	int m = 5, alan, internalfrag, t = 1, sayac2y, yr = 0, i, u = 0, yedek = 0;
	char process[20];
	int bellek[11] = { 1,2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };//1024 bellegýn parcalarý
	struct node* yeniptr = NULL, * silptr = NULL, * yrptr = head;
	char bos[20] = "free";
	int baslat = 0;
	struct node* temp = NULL;
	//ýnternal fragmantasyonlar için
	int gir;
	struct  INTERNAL* bas = NULL, * yeni = NULL;
	abas = malloc(sizeof(struct INTERNAL));
	///ABAS AMACI INTERNAL STRUCTIN BAÞI

	struct node* sonrakiptr = NULL;
	printf("**** MEMORY ****\n");
	printf("Block-1: free – 1024M");
	printf("***********\n");

	while (m != 0) {
		printf("\n Enter 0(EXIT), 1(request), 2(release): ");
		scanf("%d", &m);
		gir = 0;
		if (m == 0) {
			printf("EXIT");
		}

		else if (m == 1) {//buraya herkes girecek.ilk head olmasý onemlý deðil
			u++;//kacýncý gýrýs
			//alan buyuk oldugunda
			printf("\n Enter process name and requested space(M):");
			scanf("%s%d", process, &alan);
			if (alan > 1024) {
				printf("yeterli alan yok BITTI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
				return -1;
			}

			if (head != NULL) {
				if (head->MB == 1024) {
					t = 1;
					head = NULL;
					abas = NULL;
					u = 1;
				}
			}
			for (int i = 10; i >= 0; i--) {

				if (alan > bellek[i]) {//UYGUN ALANI BUL

					baslat = i + 1;//

					internalfrag = bellek[i + 1] - alan;
					//INTERNAL ICIN
					yeni = malloc(sizeof(struct INTERNAL));
					strcpy(yeni->durum, process);
					yeni->frag = internalfrag;
					yeni->ptr1 = NULL;
					if (u == 1) {
						abas = yeni;
						bas = abas;
					}
					else {
						while (bas->ptr1 != NULL) {
							bas = bas->ptr1;
						}
						bas->ptr1 = yeni;
						bas = bas->ptr1;
					}
					//INTERNAL ÝÇÝN 
					///head

					yeniptr = malloc(sizeof(struct node));//HEAD ÝÇÝN 
					if (yeniptr != NULL) {
						strcpy(yeniptr->durum, process);
						yeniptr->MB = bellek[i + 1];
						yeniptr->ptr = NULL;


						if (head == NULL) {//ÝLK OLUSTUGUNDA
							head = yeniptr;//BELLEK UZERINDE ÝLERLEMEN ÝÇÝN
							yrptr = head;
						}

						break;
					}
				}
			}
			if (t == 1) {//HEAD KISMINDA GÝRSÝN
				for (int i = baslat; i < 10; i++) {



					temp = malloc(sizeof(struct node));//YENI OLUSCAK BASKA DUGUM

					strcpy(temp->durum, bos);//temp boþluk

					temp->MB = bellek[i];
					temp->ptr = NULL;
					while (yrptr->ptr != NULL) {
						yrptr = yrptr->ptr;
					}
					yrptr->ptr = temp;
					yrptr = yrptr->ptr;


				}
				t++;
				yazdýr();
			}

			else {//ilki bellek dýzýsýne bakardý burada  lýnked lýst bakacagýz oyuzden ayrý 

				struct node* gezmeptr = head;
				struct node* newptr = NULL, * sonptr = NULL;
				struct node* tutptr = NULL, * tut2ptr = NULL;
				struct node* oncekiptr = NULL;
				int tut = 0;
				int yralan;
				int  sayac = 0;


				while (gezmeptr != NULL) {
					if (alan <= gezmeptr->MB && tut == strcmp(gezmeptr->durum, bos)) {//UYGUN YER SECILIR.
						if (head == NULL) {
							tutptr = head;
							tut2ptr = head->ptr;
						}
						else {
							tutptr = oncekiptr;
							tut2ptr = gezmeptr->ptr;
						}

						//silptr = gezmeptr;
						//free(silptr);

						yralan = gezmeptr->MB / 2;
						if (alan < yralan) {//ALAN KUCUK AMA O BOLGENIN YARISINDAN DAMI KUCUK
							while (alan <= yralan) {
								sayac++;//OLUSTURULACAK 2^N NODE VAR.
								yralan = yralan / 2;
							}

						}

						else if (alan > yralan) {//HAYIR KUCUK DEÐÝL.TAMAMINI ALCAK
							sayac = 0;

						}
						else if (alan == yralan) {
							sayac = 1;
						}
						sayac2y = pow(2, sayac);//NODE SAYISI



						yr = sayac2y;



						tutptr->ptr = yeniptr;//onceye yeniyi eklemýssýn

						yrptr = head;
						for (i = 0; i < sayac2y - 1; i++) {//SAYAC2Y-1


							sonptr = malloc(sizeof(struct node));
							strcpy(sonptr->durum, bos);
							sonptr->MB = (gezmeptr->MB) / yr;
							sonptr->ptr = NULL;


							while (yrptr->ptr != NULL) {
								yrptr = yrptr->ptr;

							}
							yrptr->ptr = sonptr;
							yrptr = yrptr->ptr;
							yr = yr / 2;
							if (yr == 1) {
								break;
							}


						}

						while (yrptr->ptr != NULL) {
							yrptr = yrptr->ptr;
						}
						yrptr->ptr = tut2ptr;
						yedek = 1;

						gir = 1;


					}///içeriye girenleri çýkart
					if (yedek == 1) {
						yedek = 0;
						break;
					}
					oncekiptr = gezmeptr;
					gezmeptr = gezmeptr->ptr;

				}
				if (gir == 0) {
					printf("yetersiz alan BITTI !!!!!!!!!!!!!!!!!!!!");
					return -1;
				}

				yazdýr();
			}
		}
		///2 SECÝM YAPILIRSA YENI DELETE
		if (m == 2) {

			printf("process name:");
			scanf("%s", &process);
			if (head == NULL || (head->ptr == NULL && 1 == strcmp(head->ptr, "free"))) {
				printf("dizi yok ki");
				return -1;
			}
			struct node* cptr = head;
			struct node* optr = NULL;
			struct node* soptr = head->ptr;
			struct node* tara = head;
			struct node* collect = NULL;
			struct INTERNAL* pw = abas;
			struct INTERNAL* ow = NULL;
			struct INTERNAL* sow = abas->ptr1;

			int i = 1;
			int d = 0;
			int f = 0;
			int r = 0;
			int g = 0;
			int w = 0;
			int w1 = 0;
			while (cptr != NULL && (0 != strcmp(cptr->durum, process))) {//processi bulmaya calýsýyorum


				optr = cptr;
				cptr = cptr->ptr;
				if (cptr == NULL && -0 != strcmp(optr->durum, process)) {
					printf("bu  isimle bir process yok");
					return -1;

				}
				soptr = cptr->ptr;
			}


			strcpy(cptr->durum, "free");
			///INTERNAL ICIN BUL VE ORAYI BOSALT
			while (pw != NULL && (0 != strcmp(pw->durum, process))) {//processi bulmaya calýsýyorum


				ow = pw;
				pw = pw->ptr1;
				sow = pw->ptr1;
			}
			if (pw == abas) {
				abas = sow;

			}
			else if (pw->ptr1 == NULL) {
				ow->ptr1 = NULL;
			}
			else {
				ow->ptr1 = sow;
			}
			/////////////////////////
			while (cptr != NULL && cptr->MB != 1024) {
				if (cptr != head) {
					if (d == strcmp(cptr->durum, "free") && (f == strcmp(optr->durum, "free") && optr->MB == cptr->MB)) {
						collect = malloc(sizeof(struct node));
						collect->MB = cptr->MB + optr->MB;
						strcpy(collect->durum, "free");
						collect->ptr = cptr->ptr;

						if (optr != head) {
							while (tara->ptr != optr) {
								tara = tara->ptr;
							}
							tara->ptr = collect;
							optr = collect;
						}
						if (head == optr) {
							head = collect;
						}

						cptr = collect->ptr;

						w = 5;
					}
				}

				if (soptr != NULL) {
					if (d == strcmp(cptr->durum, "free") && (r == strcmp(soptr->durum, "free") && soptr->MB == cptr->MB)) {
						collect = malloc(sizeof(struct node));
						collect->MB = cptr->MB + soptr->MB;
						strcpy(collect->durum, "free");
						if (optr == NULL) {
							head = collect;
							soptr = cptr->ptr;

						}
						else {
							optr->ptr = collect;
						}

						collect->ptr = soptr->ptr;



						cptr = collect;
						soptr = cptr->ptr;

						w1 = 5;
					}
				}
				if (w != 5 && w1 != 5) {
					break;
				}
				w = 0;
				w1 = 0;
			}


			yazdýr();

		}

		if (m != 0 && m != 1 && m != 2) {
			printf("GECERSIZ ISLEM  BITTI !!!!!!!!!!!!!");
			return -1;
		}



	}
	return 0;

}