#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <conio.h>
/*
 * �㭪樨 ࠡ��� � ���ᨢ���
*/
int PrntArray(int *arr, int length);            //�뢮��� ���ᨢ �� �࠭, �����頥� �㬬� ����⮢
int FillArrayRandomizd(int *arr, int length);   //�������� ���ᨢ �������� ������ �ᥢ����砩�묨 �᫠��, ��ৢ�頥� �㬬� ��� �ᥫ
int FillArrayAscending(int *arr, int length);   //� �� + ������ ���ᨢ � ��אַ� ���浪�
int FillArrayDscending(int *arr, int length);   //� �� + ������ ���ᨢ � ���⭮� ���浪�
int CalculateSequences(int *arr, int length);   //������� �᫠ �਩ � ���ᨢ�
void CopyArray(int *arrSrc, int *arrDst, int length);   //������� ������ ���ᨢ� arrSrc � arrDst
void MirrorArray(int *arr, int length);         //��ࠧ��� ���冷� ᫥������� ����⮢ � ���ᨢ�
/*
 * �㭪樨 ���஢��
*/
void SelectionSort(int *arr, int length, int *M, int *C);   //���஢�� ��⮤�� ��אַ�� �롮�
void BubbleSort(int *arr, int length, int *M, int *C);      //����쪮��� ���஢��
void CoctailSort(int *arr, int length, int *M, int *C);     //襩��ୠ� ���஢��
void InsertionSort(int *arr, int length, int *M, int *C);   //���஢�� ��⠢����
void ShellSort(int *arr, int length, int *M, int *C);       //���஢�� �����, ��᫥����⥫쭮��� 蠣�� �����ठ/���� 1,3,7,15,31,...,((2^k)-1)
//+ ��ࠬ���, ����
const int alg_count = 5;                                    //�᫮ ॠ���������� �����⬮�
/*
 * �㭪樨 �ᯮ����⥫��
*/
int PrngRanged(int exp, int seed); //�����頥� ��ᥢ����砩��� �᫮ � ��������� 10^exp ... (10^(exp+1))-1; �.�. 10...99 ��� exp=1

struct algorythm {char id[10]; char name[40]; void (*falg)(int *arr, int length, int *M, int *C);} algorythms[] = {
    {"selection","����஢�� ��⮤�� ��אַ�� �롮�",SelectionSort},
    {"bubble","����쪮��� ���஢��",BubbleSort},
    {"coctail","�����ୠ� ���஢��",CoctailSort},
    {"insertion","����஢�� ��⠢����",InsertionSort},
    {"shell","����஢�� �����",ShellSort},
    };


int PrngRanged(int exp, int seed){
    // �᫮ num � ��������� upper...lower ����� ���� ᣥ��ࠨ஢��� ��� num = (rand() % (upper - lower + 1)) + lower
    srand(seed);
    int lim_l = (int)pow(10,exp);
    int lim_h = lim_l*9;
    return rand()%lim_h+lim_l;
}

int PrntArray(int *arr, int length){
    int sum = 0;
    for (int i=0;i<length;i++){
        printf("[%u] ",*arr);
        sum += *arr++;
    }
    printf("\n");
    return sum;
}

int FillArrayRandomizd(int *arr, int length){
    int exp = (int)log10f(length);
    if (exp>3){
        return -1; //avoid overflow when calculating int sum
    }
    //struct timespec ts;
    //timespec_get(ts, time(NULL));
    int sum = 0;
    for (int i=0;i<length;i++){
        sum += *arr++ = PrngRanged(exp,time(NULL)*i);
    }
    return sum;
}

int FillArrayAscending(int *arr, int length){
    int i=0;
    int sum = FillArrayRandomizd(arr, length);
    SelectionSort(arr, length, &i, &i);
    return sum;
}

int FillArrayDscending(int *arr, int length){
    int i=0;
    int sum = FillArrayRandomizd(arr, length);
    SelectionSort(arr, length, &i, &i);
    MirrorArray(arr,length);
    return sum;
}

int CalculateSequences(int *arr, int length){
    //�ਥ� ���뢠���� ���뢠��� ��᫥����⥫쭮��� ����⮢ ���ᨢ� ���ᨬ��쭮� �����
    if (length<=1)
    {
        return length;
    }
    int counter = 1;
    int prev = *arr++;
    int curr;
    for (int i=1;i<length;i++){
        curr = *arr++;
        if (curr<prev){
            counter++;
        }
        prev = curr;
    }
    return counter;
}

void CopyArray(int *arrSrc, int *arrDst, int length){
    for (int i=0;i<length;i++){
        //arrDst[i] = arrSrc[i];
        *arrDst++ = *arrSrc++;
    }
}

void MirrorArray(int *arr, int length){
    int *arrTemp = (int *)malloc(length*sizeof(int));
    int i,j;
    for (i=0,j=length-1;i<length;i++,j--){
        arrTemp[j] = arr[i];
    }
    for (i=0;i<length;i++){
        arr[i] = arrTemp[i];
    }
    free(arrTemp);
}

void SelectionSort(int *arr, int length, int *M, int *C){
    *M = *C = 0;
    int *first; int *smallest;
    int temp,i,j;
    for (i=0;i<length-1;i++){
        first = &arr[i];
        smallest = &arr[i];
        for (j=i+1;j<length;j++){
            (*C)++;
            if (*smallest>arr[j]){
                smallest = &arr[j];
            }
        }
        *M += 3;
        temp = *first;
        *first = *smallest;
        *smallest = temp;
    }
}

void BubbleSort(int *arr, int length, int *M, int *C){
    *M = *C = 0;
    int temp,i,j;
    for (i=0;i<length-1;i++){
        for (j=length-1;j>i;j--){
            (*C)++;
            if (arr[j]<arr[j-1]){
                *M += 3;
                temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
} // � �����襬 ��砥 � ����� ����⭮�� ��祬�-�

void CoctailSort(int *arr, int length, int *M, int *C){
    *M = *C = 0;
    int temp,i;
    int left = 0, right = length-1;
    int lastSwap = 0;
    while (left<right){
        for (i=right;i>left;i--){
            (*C)++;
            if (arr[i]<arr[i-1]){
                *M += 3;
                temp = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = temp;
                lastSwap = i;
            }
        }
        if (lastSwap==left) break;
        left = lastSwap;
        for (i=left;i<right;i++){
            (*C)++;
            if (arr[i]>arr[i+1]){
                *M += 3;
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                lastSwap = i;
            }
        }
        if (lastSwap==right) break;
        right = lastSwap;
    }
} // � �����襬 ��砥 � ����� ����⭮�� ��祬�-�

void InsertionSort(int *arr, int length, int *M, int *C){
    /**M = *C = 0;
    int i,j,temp;
    for (i=1;i<length;i++){
        temp = arr[i];
        for (j=i-1;((j>=0)&&(arr[j]>temp));j--){
            arr[j+1] = arr[j];
        }
        arr[j+1] = temp;
    }*/
    *M = *C = 0;
    int i,j,temp;
    for (i=1;i<length;i++){
        temp = arr[i];
        (*M)++;
        for (j=i-1;j>=0;j--){
            (*C)++;
            if (arr[j]>temp){
                (*M)++;
                arr[j+1] = arr[j];
            } else break;
        }

        arr[j+1] = temp;
        (*M)++;
    }
}

void ShellSort(int *arr, int length, int *M, int *C){
    *M = *C = 0;
    //蠣 ���஢�� k, ������⢮ ���஢�� h
    //k = (2^h)-1; ����. h = log2(length)-1
    int h,k,i,j,temp;
    for (h=log2(length)-1;h>=1;h--){
        k = exp2(h)-1;
        //printf("k=%d, h=%d\n",k,h);
        for (i=k;i<length;i++){
                temp = arr[i];
                (*M)++;
                for (j=i-k;j>=0;j-=k){
                    (*C)++;
                    if (arr[j]>temp){
                        (*M)++;
                        arr[j+k] = arr[j];
                    } else break;
                }
                arr[j+k] = temp;
                (*M)++;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc<3){
        printf("������ ��㬥���: �����_���ᨢ� ���冷�_���஢�� ⨯_���஢��1 [⨯_���஢��2 ... n]\n");
        printf("�����_���ᨢ�: �� 2 �� 9999\n");
        printf("���冷�_���஢��: RND ASC DSC\n");
        printf("⨯�_���஢��: selection bubble coctail insertion shell\n");
        printf("���ਬ��: algo.exe 100 RND bubble coctail\n");
        return -1;
    }
    int length;
    if ((length=atoi(argv[1]))<1){
        printf("�� 㪠���� ����� ���ᨢ�!\n");
        return -1;
    } else if (length<2){
        length = 2;
    } else if (length>9999){
        length = 9999;
    }
    int *arrSrc, *arrDst;
    int M, C, seq, sum;
    for (;;){
        arrSrc = malloc(length*sizeof(int));
        arrDst = malloc(length*sizeof(int));
        M = C = seq = sum = 0;
        if (strstr(argv[2],"RND")){
            sum = FillArrayRandomizd(arrSrc,length);
        } else if (strstr(argv[2],"ASC")){
            sum = FillArrayAscending(arrSrc,length);
        } else if (strstr(argv[2],"DSC")){
            sum = FillArrayDscending(arrSrc,length);
        } else {
            printf("�� ����� ���冷� ���஢�� ��室���� ���ᨢ�!\n");
            return -1;
        }
        if (sum>0){
            system("cls");
            printf("��室�� ���ᨢ:\n");
            PrntArray(arrSrc,length);
            seq = CalculateSequences(arrSrc,length);
            printf("������ ���ᨢ� = %d; �㬬� ����⮢ = %d; �਩ = %d\n",length,sum,seq);
        for (int i=3;i<argc;i++){
            struct algorythm *al = algorythms;
            for (int j=0;j<alg_count;j++,al++){
                if (strstr(argv[i],al->id)){
                    printf("\n%s:\n",al->name);
                    CopyArray(arrSrc, arrDst, length);
                    al->falg(arrDst,length,&M,&C);
                    printf("�ࠢ����� C = %d; ����뫮� M = %d\n",C,M);
                    sum = PrntArray(arrDst,length);
                    seq = CalculateSequences(arrDst,length);
                    printf("������ ���ᨢ� = %d; �㬬� ����⮢ = %d; �਩ = %d\n",length,sum,seq);
                    break;
                }
            }
        }
        }
        free(arrSrc);
        free(arrDst);
        printf("\n������ ESC ��� �����襭�� ��� ���� ������� ��� �����\n");
        char ch = getch();
        system("cls");
        switch(ch){
            case '\e': return 0;
        }
    }
    return 0;
}
//https://en.wikipedia.org/wiki/Sorting_algorithm
