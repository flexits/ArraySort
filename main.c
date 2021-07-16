#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <conio.h>
/*
 * �㭪樨 ࠡ��� � ���ᨢ���
 */
uintmax_t PrntArray(int *arr, size_t length);            //�뢮��� ���ᨢ arr ����� length �� �࠭, �����頥� �㬬� ����⮢
uintmax_t FillArrayRandomizd(int *arr, size_t length);   //�������� ���ᨢ �������� ������ �ᥢ����砩�묨 �᫠��, ��ৢ�頥� �㬬� ��� �ᥫ
uintmax_t FillArrayAscending(int *arr, size_t length);   //� �� + ������ ���ᨢ � ��אַ� ���浪�
uintmax_t FillArrayDscending(int *arr, size_t length);   //� �� + ������ ���ᨢ � ���⭮� ���浪�
size_t CalculateSequences(int *arr, size_t length);      //������� �᫠ �਩ � ���ᨢ�
void CopyArray(int *arrSrc, int *arrDst, size_t length); //������� ������ ���ᨢ� arrSrc � arrDst
void MirrorArray(int *arr, size_t length);               //��ࠧ��� ���冷� ᫥������� ����⮢ � ���ᨢ�
/*
 * �㭪樨 ���஢��
 */
// � - �᫮ ��६�饭��, � - �᫮ �ࠢ����� ����⮢ ���ᨢ�
void SelectionSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C);   //���஢�� ��⮤�� ��אַ�� �롮�
void BubbleSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C);      //����쪮��� ���஢��
void CoctailSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C);     //襩��ୠ� ���஢��
void InsertionSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C);   //���஢�� ��⠢����
void ShellSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C);       //���஢�� �����, ��᫥����⥫쭮��� 蠣�� �����ठ 1,3,7,15,31,...,((2^k)-1)
void HeapSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C);        //��ࠬ����쭠� ���஢��
void QuickSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C);       //���஢�� ���� //����⪠ ��� qsrt()
/*
 * �㭪樨 �ᯮ����⥫��
 */
static inline int PrngRanged(int exp, int seed);     //�����頥� �ᥢ����砩��� �᫮ � ��������� 10^exp ... (10^(exp+1))-1; �.�. 10...99 ��� exp=1
static inline void swap(int *a, int *b);             //����� ���⠬� ���祭�� ���� ��६�����
static inline void heapify (int *arr, size_t size, size_t node, uintmax_t *M, uintmax_t *C);     //����஥��� ��ࠬ���, ��稭�� � ����� ���ᨢ� node
static inline size_t find_pivot (int *arr, size_t start, size_t end, uintmax_t *M, uintmax_t *C);//��宦����� ���୮�� ����� � �����⬥ ����
static inline void qsrt (int *arr, size_t start, size_t end, uintmax_t *M, uintmax_t *C);        //४��ᨢ��� ॠ������ �����⬠ ����
// ��� ���� �ணࠬ��: �᫮ �����⬮� � �� ����᫥��� � 㪠��⥫ﬨ �� �㭪樨
static const int alg_count = 7;
static const struct algorythm {char id[10]; char name[40]; void (*falg)(int *arr, size_t length, uintmax_t *M, uintmax_t *C);} algorythms[] = {
    {"selection","����஢�� ��⮤�� ��אַ�� �롮�",SelectionSort},
    {"bubble","����쪮��� ���஢��",BubbleSort},
    {"coctail","�����ୠ� ���஢��",CoctailSort},
    {"insertion","����஢�� ��⠢����",InsertionSort},
    {"shell","����஢�� �����",ShellSort},
    {"heap","��ࠬ����쭠� ���஢��",HeapSort},
    {"quick","����஢�� ����",QuickSort},
    };

static inline int PrngRanged(int exp, int seed){
    // �᫮ num � ��������� upper...lower ����� ���� ᣥ��ࠨ஢��� ��� num = (rand() % (upper - lower + 1)) + lower
    srand(seed);
    if (exp>8){ //avoid int overflow
        return rand();
    } else{
        int lim_l = (int)pow(10,exp);
        int lim_h = lim_l*9;
        return rand()%lim_h+lim_l;
    }
}

static inline void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

uintmax_t PrntArray(int *arr, size_t length){
    uintmax_t sum = 0;
    bool prnt = (length < 1000);
    for (size_t i=0;i<length;i++){
        if (prnt){
            printf("[%u] ",*arr);
        }
        sum += *arr++;
    }
    printf("\n");
    return sum;
}

uintmax_t FillArrayRandomizd(int *arr, size_t length){
    int exp = (int)log10f(length);
    /*struct timespec ts;
    timespec_get(ts, time(NULL));*/
    uintmax_t sum = 0;
    for (size_t i=0;i<length;i++){
        sum += (*arr++) = PrngRanged(exp,time(NULL)*i);
    }
    return sum;
}

uintmax_t FillArrayAscending(int *arr, size_t length){
    uintmax_t i=0;
    uintmax_t sum = FillArrayRandomizd(arr, length);
    QuickSort(arr, length, &i, &i);
    return sum;
}

uintmax_t FillArrayDscending(int *arr, size_t length){
    uintmax_t sum = FillArrayAscending(arr, length);
    MirrorArray(arr,length);
    return sum;
}

size_t CalculateSequences(int *arr, size_t length){
    //�ਥ� ���뢠���� ���뢠��� ��᫥����⥫쭮��� ����⮢ ���ᨢ� ���ᨬ��쭮� �����
    if (length<=1)
    {
        return length;
    }
    size_t counter = 1;
    int prev = *arr++;
    int curr = prev;
    for (size_t i=1;i<length;i++){
        curr = *arr++;
        if (curr<prev){
            counter++;
        }
        prev = curr;
    }
    return counter;
}

void CopyArray(int *arrSrc, int *arrDst, size_t length){
    for (size_t i=0;i<length;i++){
        *arrDst++ = *arrSrc++;
    }
}

void MirrorArray(int *arr, size_t length){
    int *arrTemp = malloc(length*sizeof(int));
    size_t i,j;
    for (i=0,j=length-1;i<length;i++,j--){
        arrTemp[j] = arr[i];
    }
    for (i=0;i<length;i++){
        arr[i] = arrTemp[i];
    }
    free(arrTemp);
}

void SelectionSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C){
    *M = *C = 0;
    int *first, *smallest;
    size_t i,j;
    for (i=0;i<length-1;i++){
        first = &arr[i];
        smallest = &arr[i];
        for (j=i+1;j<length;j++){
            (*C)++;
            if (*smallest>arr[j]){
                smallest = &arr[j];
            }
        }
        swap(first, smallest);
        *M += 3;
    }
}

void BubbleSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C){
    *M = *C = 0;
    size_t i,j;
    for (i=0;i<length-1;i++){
        for (j=length-1;j>i;j--){
            (*C)++;
            if (arr[j]<arr[j-1]){
                *M += 3;
                swap(&arr[j], &arr[j-1]);
            }
        }
    }
}

void CoctailSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C){
    *M = *C = 0;
    size_t i, lastSwap = 0, left = 0, right = length-1;
    while (left<right){
        for (i=right;i>left;i--){
            (*C)++;
            if (arr[i]<arr[i-1]){
                *M += 3;
                swap(&arr[i], &arr[i-1]);
                lastSwap = i;
            }
        }
        if (lastSwap==left) break;
        left = lastSwap;
        for (i=left;i<right;i++){
            (*C)++;
            if (arr[i]>arr[i+1]){
                *M += 3;
                swap(&arr[i], &arr[i+1]);
                lastSwap = i;
            }
        }
        if (lastSwap==right) break;
        right = lastSwap;
    }
}

void InsertionSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C){
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
    intmax_t i, j;
    int temp;
    for (i=1;i<length;i++){
        temp = arr[i];
        (*M)++;
        for (j=i-1;j>=0;j--){ //size_t j always >=0
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

void ShellSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C){
    *M = *C = 0;
    //蠣 ���஢�� k, ������⢮ ���஢�� h
    //k = (2^h)-1; ����. h = log2(length)-1
    int h,k,temp;
    intmax_t i,j;
    for (h=log2(length)-1;h>=1;h--){
        k = exp2(h)-1;
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

static inline void heapify (int *arr, size_t size, size_t node, uintmax_t *M, uintmax_t *C){
    size_t largest = node;
    size_t lchild = 2*node+1;
    size_t rchild = 2*node+2;
    (*C)++;
    if ((lchild<size)&&(arr[lchild]>arr[largest])){
        largest = lchild;
        }
    (*C)++;
    if ((rchild<size)&&(arr[rchild]>arr[largest])){
        largest = rchild;
    }
    if (largest!=node){
        *M += 3;
        swap(&arr[largest],&arr[node]);
        heapify(arr, size, largest, M, C);
    }
}

void HeapSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C){
    *M = *C = 0;
    for (intmax_t i=length/2; i>=0; i--){
        heapify(arr, length, i-1, M, C);
    }
    for (intmax_t i=length-1; i>=0; i--){
        *M += 3;
        swap(&arr[0],&arr[i]);
        heapify(arr, i, 0, M, C);
    }
}

static inline size_t find_pivot (int *arr, size_t start, size_t end, uintmax_t *M, uintmax_t *C){
    size_t i = start;
    size_t j = end;
    int pivot = arr[(start+end)/2];
    //int pivot = arr[start];
    for (;;){
        while (arr[i]<pivot){
            i++;
            (*C)++;
        }
        while (arr[j]>pivot){
            j--;
            (*C)++;
        }
        (*C)++;
        if (i>=j){
            break;
        }
        *M += 3;
        swap(&arr[i++],&arr[j--]);
    }
    return j;
}

static inline void qsrt (int *arr, size_t start, size_t end, uintmax_t *M, uintmax_t *C){
    if (start<end){
        size_t ipivot = find_pivot(arr, start, end, M, C);
        qsrt(arr, start, ipivot, M, C); //���. ����  [0, indpivot]
        qsrt(arr, ipivot+1, end, M, C); //�ࠢ. ���� [indpivot, length-1]
    }
}

void QuickSort(int *arr, size_t length, uintmax_t *M, uintmax_t *C){
    *M = *C = 0;
    qsrt(arr,0,length-1, M, C);
}

int main(int argc, char *argv[])
{
    if (argc<3){
        printf("������ ��㬥���: �����_���ᨢ� ���冷�_���஢�� ⨯_���஢��1 [⨯_���஢��2 ... n]\n");
        printf("�����_���ᨢ�: ������ 2, ���ᨬ�\n");
        printf("���冷�_���஢��: RND ASC DSC\n");
        printf("⨯�_���஢��: selection bubble coctail insertion shell heap quick\n");
        printf("���ਬ��: algo.exe 100 RND coctail shell\n");
        return -1;
    }
    size_t length;
    if ((length=atoi(argv[1]))<1){
        printf("�� 㪠���� ����� ���ᨢ�!\n");
        return -1;
    } else if (length<2){
        length = 2;
    } /*else if (length>9999){
        length = 9999; // 100 000 000 max tested, *10 = error
    }*/
    int *arrSrc, *arrDst;
    size_t seq;
    uintmax_t sum, M, C;
    for (;;){
        if ((arrSrc = malloc(length*sizeof(int))) == NULL){
            printf("�訡�� �뤥����� �����!\n");
            return -1;
        }
        if ((arrDst = malloc(length*sizeof(int))) == NULL){
            printf("�訡�� �뤥����� �����!\n");
            return -1;
        }
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
            printf("������ ���ᨢ� = %"PRIu64"; �㬬� ����⮢ = %"PRIu64"; �਩ = %"PRIu64"\n",length,sum,seq);
        for (int i=3;i<argc;i++){
            const struct algorythm *al = algorythms;
            for (int j=0;j<alg_count;j++,al++){
                if (strstr(argv[i],al->id)){
                    printf("\n%s:\n",al->name);
                    CopyArray(arrSrc, arrDst, length);
                    al->falg(arrDst,length,&M,&C);
                    printf("�ࠢ����� C = %"PRIu64"; ����뫮� M = %"PRIu64"\n",C,M);
                    sum = PrntArray(arrDst,length);
                    seq = CalculateSequences(arrDst,length);
                    printf("������ ���ᨢ� = %"PRIu64"; �㬬� ����⮢ = %"PRIu64"; �਩ = %"PRIu64"\n",length,sum,seq);
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
//https://www.programiz.com/dsa/heap-sort
//https://neerc.ifmo.ru/wiki/index.php?title=%D0%91%D1%8B%D1%81%D1%82%D1%80%D0%B0%D1%8F_%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0
