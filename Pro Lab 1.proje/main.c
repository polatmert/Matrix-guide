#include <ctype.h>//silinebilir
#include <allegro.h>
#include <stdio.h>
#include <math.h>
#define graf_genislik 800
#define graf_yukseklik 600

int hadamard_fonksiyon(int matris[16][16],int n);
int mds_fonksiyon(int matris[16][16],int n);
int simetrik_fonksiyon(int matris[16][16],int n);
int dairesel_fonksiyon(int matris[16][16],int n);


 int ikilik_det( int matris[16][16], int x, int y) {

	return (matris[0][0]*matris[x][y]) - (matris[0][y]*matris[x][0]);

}

 int determinant( int matris[16][16],int m) {

	 int b[16][16]= { };
	int i,j;

	if(m==2) {
		return (matris[0][0]*matris[1][1]) - (matris[0][1]*matris[1][0]);
	}

	if(matris[0][0]==0) {
		for(i=0;i<m;i++) {
			if(matris[0][i]!=0)
                {
				for(j=0;j<m;j++)
                    {
					int tmp=matris[j][0];
					matris[j][0]=matris[j][i];
					matris[j][i]=tmp;
                    }
                    break;

			}
		}
		if(i==m)
			return 0;
	}
	for(i=1;i<m;i++) {
		for(j=1;j<m;j++) {
			b[i-1][j-1]=ikilik_det(matris,i,j);
		}
	}


	return (1/pow(matris[0][0],m-2)) * determinant(b,m-1);

}

int sayi_giris()//allegro ekranýna sayi girmek için
{
    if ( key[KEY_1]||key[KEY_1_PAD])
    {
        return 1;
    }
    if ( key[KEY_2]||key[KEY_2_PAD] )
    {
        return 2;
    }
    if ( key[KEY_3] ||key[KEY_3_PAD])
    {
        return 3;
    }
    if ( key[KEY_4] ||key[KEY_4_PAD])
    {
        return 4;
    }
    if ( key[KEY_5]||key[KEY_5_PAD] )
    {
        return 5;
    }
    if ( key[KEY_6] ||key[KEY_6_PAD])
    {
        return 6;
    }
    if ( key[KEY_7]||key[KEY_7_PAD])
    {
        return 7;
    }
    if ( key[KEY_8] ||key[KEY_8_PAD])
    {
        return 8;
    }
    if ( key[KEY_9] ||key[KEY_9_PAD])
    {
        return 9;
    }
    if(key[KEY_ENTER]||key[KEY_ENTER_PAD])
    {
        return -1;
    }
    if(key[62]||key[KEY_EQUALS])//key[KEY_EQUALS] -62 de kullanilabilir
    {
        return -2;
    }
    if(key[KEY_BACKSPACE])
    {
        return -3;
    }
    return 0;
}





int mds_alt_kare (int gelen_matris[16][16],int matris_boyut,int x_lik_kare)
{
    int det;
    int altkare[16][16]= {};
    int satir=0,sutun=0;
    int altkare_satir=0,altkare_sutun=0;
    int satir_kayma=0,sut_kayma=0;
//sutun saga kaydirma kaydirma
    for(sut_kayma=0; sut_kayma<(matris_boyut-x_lik_kare)+1; sut_kayma++)
    {
        sutun=sut_kayma;
        //yukaridan asagi satir tarama
        for(satir_kayma=0; satir_kayma<(matris_boyut-x_lik_kare)+1; satir_kayma++)
        {
            satir=satir_kayma;
            altkare_satir=0;
            altkare_sutun=0;
            while(satir<matris_boyut)
            {
                altkare_sutun=0;
                sutun=sut_kayma;
                while(sutun<matris_boyut)
                {
                    altkare[altkare_satir][altkare_sutun]=gelen_matris[satir][sutun];
                    altkare_sutun++;
                    sutun++;
                }
                altkare_satir++;
                satir++;
            }
            det=determinant(altkare,x_lik_kare);
            if(det==0)
                return 0;

        }
    }

        return det;
}


int digerleri_alt_kare (int gelen_matris[16][16],int matris_boyut,int x_lik_kare,FILE*dosya,int secim)
{
    int altkare[16][16]= {};

    int satir=0,sutun=0;
    int altkare_satir=0,altkare_sutun=0;
    int i=0,j=0;
    int satir_kayma=0,sut_kayma=0;

    //sutun saga kaydirma kaydirma
    for(sut_kayma=0; sut_kayma<(matris_boyut-x_lik_kare)+1; sut_kayma++)

    {
        sutun=sut_kayma;

        //yukaridan asagi satir tarama
        for(satir_kayma=0; satir_kayma<(matris_boyut-x_lik_kare)+1; satir_kayma++)
        {
            satir=satir_kayma;
            altkare_satir=0;
            altkare_sutun=0;


            while(satir<matris_boyut)
            {
                altkare_sutun=0;

                sutun=sut_kayma;

                while(sutun<matris_boyut)
                {

                    altkare[altkare_satir][altkare_sutun]=gelen_matris[satir][sutun];
                    altkare_sutun++;
                    sutun++;


                }

                altkare_satir++;
                satir++;

            }

//hadamard matrisleri yazma
            if(secim==1)
            {
                if(hadamard_fonksiyon(altkare,x_lik_kare)==1 && (x_lik_kare==2 || x_lik_kare%4==0))
                {
                    for(i=0; i<x_lik_kare; i++)
                    {
                        for(j=0; j<x_lik_kare; j++)
                        {
                            fprintf(dosya,"%d ", altkare[i][j]);
                        }
                        fputs("\n",dosya);

                    }
                    fputs("\n",dosya);
                }
            }else if(secim==2)
                 {
                 if(mds_alt_kare(altkare,matris_boyut,x_lik_kare)!=0)
                    {

                        for(i=0; i<x_lik_kare; i++)
                        {
                            for(j=0; j<x_lik_kare; j++)
                            {

                                fprintf(dosya,"%d ", altkare[i][j]);
                            }
                            fputs("\n",dosya);

                        }
                        fputs("\n",dosya);

                    }
                 }else if(secim==3)
                        {
                            if(simetrik_fonksiyon(altkare,x_lik_kare)==1)
                            {
                                for(i=0; i<x_lik_kare; i++)
                                {
                                    for(j=0; j<x_lik_kare; j++)
                                    {
                                        fprintf(dosya,"%d ", altkare[i][j]);
                                    }
                                    fputs("\n",dosya);

                                }
                                fputs("\n",dosya);
                            }
                        } else if(secim==4)
                                {
                                    if(dairesel_fonksiyon(altkare,x_lik_kare)==1)
                                    {
                                        for(i=0; i<x_lik_kare; i++)
                                        {
                                            for(j=0; j<x_lik_kare; j++)
                                            {
                                                fprintf(dosya,"%d ", altkare[i][j]);
                                            }
                                            fputs("\n",dosya);

                                        }
                                        fputs("\n",dosya);
                                    }

                                }
        }

    }
    return 0;

}





/****************************************************/

int main()
{
    FILE * hadamard=fopen("hadamard.txt","w+");
    FILE * mds_dosya=fopen("MDS.txt","w+");
    FILE * simetrik=fopen("simetrik.txt","w+");
    FILE * dairesel=fopen("dairesel.txt","w+");


    FILE*ana_matris=fopen("matris.txt","w+");
	allegro_init();
	install_keyboard();

    int sayi=NULL;
    int genislik=15,yukseklik=130;
    int matris_boyutu=1;
    int sayac=0,i=0,j=0;
    int enter_sayac=0;
    int fonk_secim=0;
    int okunan_matris[16][16];
    int x_lik_altkare=0;
	set_color_depth(32);

    set_gfx_mode(GFX_AUTODETECT_WINDOWED,graf_genislik, graf_yukseklik, 0, 0);
	BITMAP *buffer = create_bitmap(graf_genislik, graf_yukseklik);
    set_window_title("Prolab 1.Proje-ana_matris_MERT");


//matris boyut alma
while(!key[KEY_ENTER])
    {
    //textout(buffer,font,"Ok Tuslari ile Matris Boyutunu Belirtiniz:", 15,15, 0x3ef24a);
    textout(buffer,font,"Ok Tuslari ile Matris Boyutunu Belirtiniz:", 15,15, 0x3ef24a);

    blit(buffer, screen, 0, 0, 0, 0, graf_genislik, graf_yukseklik);//yazma alanini olusturur

    readkey();
        if(key[KEY_UP])
            matris_boyutu++;
        else if(key[KEY_DOWN])
            matris_boyutu--;

    textprintf(buffer, font, 370 , 15, 0xffffff, " %d ", matris_boyutu);
    blit(buffer, screen, 0, 0, 0, 0, graf_genislik, graf_yukseklik);//yazma alanini olusturur

    }
//fonksiyon secme

        textout(buffer,font,"Hadamard icin 1'e basin", 15,45,0x018def);
        textout(buffer,font,"MDS Matris icin 2'ye basin ", 15,60,0x018def);
        textout(buffer,font,"Simetrik Matris icin 3'e basin", 15,75,0x018def);
        textout(buffer,font,"Dairesel Matris icin 4'e basin", 15,90,0x018def);
        blit(buffer, screen, 0, 0, 0, 0, graf_genislik, graf_yukseklik);//yazma alanini olusturur

        readkey();
        fonk_secim=sayi_giris();
        rect(buffer, 13, fonk_secim*15+26, 270 , fonk_secim*15+42, 0xe9980a);//x1 y1 x2 y2
        textout(buffer,font,"Matrisi Giriniz", 15,115,0xf08080);

         blit(buffer, screen, 0, 0, 0, 0, graf_genislik, graf_yukseklik);//yazma alanini olusturur





    while(sayac<(matris_boyutu*matris_boyutu))
          {

//sol gorsel  ( [ )
        hline(buffer, 10, 125 ,20, 0x800000);//yatay cizgi---  x1,y1,x2
        vline(buffer, 10,125, matris_boyutu*10+135, 0x800000);//dik çizgi çizer siralama:y1,x1,y2
        hline(buffer, 10, matris_boyutu*10+135 ,20, 0x800000);//yatay cizgi---  x1,y1,x2
// sag gorsel ( ] )
        hline(buffer,matris_boyutu*75 , 125 ,matris_boyutu*75+15, 0x800000);//yatay cizgi---  x1,y1,x2
        vline(buffer, matris_boyutu*75+15 ,125,matris_boyutu*10+135, 0x800000);//dik çizgi çizer siralama:x1----y1,x1,y2
        hline(buffer, matris_boyutu*75 , matris_boyutu*10+135 ,matris_boyutu*75+15, 0x800000);//yatay cizgi---  x1,y1,x2

         blit(buffer, screen, 0, 0, 0, 0, graf_genislik, graf_yukseklik);//yazma alanini olusturur


        readkey();//program tus almak icin bekliyor

        sayi=sayi_giris();//Kullanicinin girdigi sayiyi okur****************************************

      /**dosyaya yazdirma*/

        if(sayi==(-1))//entera bastiysa
        {
            if(enter_sayac==(matris_boyutu-1))//satirin son elemani alt satira geciyor
            {
/**dosyada alt satira gec*/fputs("\n",ana_matris);
                yukseklik+=10;
                genislik=15;
                enter_sayac=0;
            }
            else //satir ortasindaysa
            {
                textout(buffer,font,"   ", genislik,yukseklik,0xffffff);
/**enter boslugu*/fputs("\t",ana_matris);
                enter_sayac++;

                genislik=enter_sayac*75;//farkli uzunlukta sayilar girildiðinde goruntu bozulmasini engeller her sayi icin 75px alan ayirir


            }
            sayac++;//enter sayisini sayar
        }

        else if(sayi==(-2))//eksi (-) girildiyse
        {
            fprintf(ana_matris,"-%d",sayi);
            textout(buffer,font,"-", genislik,yukseklik,0xffffff);
            genislik+=10;
        }
        else if(sayi==(-3))//silme islemi
            {
                genislik-=10;
                textout(buffer,font,"-", genislik,yukseklik,0x000000);

                fseek(ana_matris,-1, SEEK_CUR); //imlecin son konumundan geriye dogru siler

            }
        else//enter veya eksi degilse
        {
            fprintf(ana_matris,"%d",sayi);
            /**ekrana yazdyrma */
            textprintf(buffer, font, genislik , yukseklik, 0xfffffff, "%d", sayi);


            genislik+=10;
        }
        blit(buffer, screen, 0, 0, 0, 0, graf_genislik, graf_yukseklik);//yazma alanini olusturur
    }

        fclose(ana_matris);//yanlis yazmalari engellemek icin dosyayi kapatiyoruz
        fopen("matris.txt","r"); //dosyayi okumak icin tekrar aciyoruz


    //matris.txt den matrisi okuma
        for(i=0;i<matris_boyutu;i++){
            for(j=0;j<matris_boyutu;j++)
        {
            fscanf (ana_matris,"%d", &okunan_matris[i][j]);
        }
        }

    if(fonk_secim==1)
    {
        /*
            ana matrisin hadamard olup olmadigi kontrol edlip.dosyaya yazdiriliyor
            sonraki for dongusu, ana matrisin  alt kare matrislerini bulup onların hadamardlıgını kontrol ediyor
        */
        if(hadamard_fonksiyon(okunan_matris,matris_boyutu)==1)
        {
            fputs("Matris hadamard \r",hadamard);

        }
        else
        {
            fputs("Matris hadamard degil \r",hadamard);

        }
        for(x_lik_altkare=2; x_lik_altkare<matris_boyutu; x_lik_altkare++)
            digerleri_alt_kare(okunan_matris,matris_boyutu,x_lik_altkare,hadamard,1);

    }

    else if(fonk_secim==2)
    {

        if(mds_fonksiyon(okunan_matris,matris_boyutu)!=0)
        {
            fputs("Matris MDS \r ",mds_dosya);
        }
        else
        {
            fputs("Matris MDS degildir \r",mds_dosya);
        }

         for(x_lik_altkare=2; x_lik_altkare<matris_boyutu; x_lik_altkare++)
            {
                digerleri_alt_kare(okunan_matris,matris_boyutu,x_lik_altkare,mds_dosya,2);
            }





    }
    else if(fonk_secim==3)   //matris simetrikmi diye kontrol eder
    {
        if(simetrik_fonksiyon(okunan_matris,matris_boyutu)==1)
        {
            fputs("Matris Simetriktir \r",simetrik);
        }
        else
        {
            fputs("Matris Simetrik Degildir \r ",simetrik);
        }

        for(x_lik_altkare=2; x_lik_altkare<=matris_boyutu; x_lik_altkare++)
        {
            digerleri_alt_kare(okunan_matris,matris_boyutu,x_lik_altkare,simetrik,3);//
        }

    }
    else if(fonk_secim==4)
    {

        if(dairesel_fonksiyon(okunan_matris,matris_boyutu))
        {
            fputs("Matris Daireseldir \r  ",dairesel);

        }
        else
        {
            fputs("Matris Dairesel Degildir \r",dairesel);
        }

        for(x_lik_altkare=2; x_lik_altkare<matris_boyutu; x_lik_altkare++)
        {
            digerleri_alt_kare(okunan_matris,matris_boyutu,x_lik_altkare,dairesel,4);//
        }

    }


    fclose(ana_matris);
    fclose(simetrik);
    fclose(mds_dosya);
    fclose(dairesel);
    fclose(hadamard);




    readkey();//Matris girildikten sonra ekranin kapanmasini engeller
	return 0;
}

END_OF_MAIN();


int  hadamard_fonksiyon(int matris[16][16],int n)
{

    int i,j;
    int hadamard_kontrol=1;
    int a=n-1,b=n-1;
    for (j=0; j<n; j++)
    {
        for(i=0; i<n; i++)
        {
            if(matris[i][j]!=matris[a][b])
            {
                hadamard_kontrol=0;
            }

            else
                a--;
        }

        a=n-1;

        b--;

    }

    return hadamard_kontrol;



}






int mds_fonksiyon(int matris[16][16],int matris_boyutu)
{
    int i;
	 int sonuc=1;

	for(i=2;i<matris_boyutu;i++)
        {

        sonuc=mds_alt_kare(matris,matris_boyutu,i);
        if(sonuc==0)
            {
            break;
            }
        }
        if(sonuc!=0)
        {


            }


        return sonuc;
}




int  simetrik_fonksiyon(int matris[16][16],int n)

{
    int i,j;
    int kontrol=1;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(matris[i][j]!=matris[j][i])
               {
                kontrol=0;
                break;
               }
        }
    }
    return kontrol;
}

int dairesel_fonksiyon(int matris[16][16],int n)
{
    int i,j,a,b;

    int kontrol[16]= {};



    for (i=0; i<n; i++)
        kontrol[i]=matris[i][0];
    int sonuc=1;
    for (j=0; j<n; j++)
    {
        for (b=0; b<n; b++)
        {
            for (a=0; a<n; a++)
            {
                if(kontrol[a]!=matris[a][b])
                    sonuc=0;
            }
            for (i=0; i<n-1; i++)
            {
                a=kontrol[i];
                kontrol[i]=kontrol[n-1];
                kontrol[n-1]=a;
            }
        }
    }

    return sonuc;
}



