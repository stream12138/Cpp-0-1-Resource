#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
#include <string.h>
#include <math.h>
typedef struct TREE {
    char data;//�����ĸ
    char info;//�����ĸ�ĸ�ֵ
    struct TREE *lchild;
    struct TREE *rchild;
} TREE;
/*****�������Ķ���*****/
typedef struct {
    TREE *top;
    TREE *base;
    int S_Size;
} S;
/****ջ�Ķ���****/

typedef struct QNode {
    TREE *data;
    struct QNode *next;
} QNode;
typedef struct Quene {
    QNode *front;
    QNode *rear;
} Quene;
/*****���ж���*****/
void InitS(S *S);
void push(S *S, TREE a);
TREE pop(S *S);
TREE gettop(S S);
int stackempty(S S);
void InitQuene(Quene *Q);
void EnQuene(Quene *Q, TREE* a);
TREE* DeQuene(Quene *Q);
char cmp(char a, char b);
TREE CreateTree(int *count, char v[][SIZE]);
char operate(TREE *T);
void calculation(TREE *T, char(*q)[][SIZE], int i, int count);
void calculate(TREE T, char *q, int count, char v[][SIZE]);
TREE CreateTree_0and1(int count);
void Visit(TREE *T, char*q, char *p, int *k, int *j);
void get(TREE T, int count, char*q);
char* arrange(int count);
void DestroyTree(TREE *T);
/*****����Ϊ��������*****/
int main() {

    TREE T;
    int count = 0; //�����¼�����
    char *arrangement;//��¼���н����ָ��
    char v[SIZE][SIZE];//��ֵ��
    int k = 10; //�˵�ѡ��
    int i, j; //���������ֵ��λ��
    char c;//���������ַ�
    int b = 0; //������'0','1'
    int r = 1; //����
    int x;//x����������ֵ��Ĵ�ӡ

    for(; k != 0;) {

        printf("����������ѡ��\n1.������ʽ \n2.��ӡ��ֵ�����ж��Ƿ�Ϊ����ʽ\n3.�Լ����븳ֵ���Ҵ�ӡ��ֵ�������Ӧ�Ľ��\n0.�˳�\n");
        scanf("%d", &k);

        switch(k) {
        case 1:
            T = CreateTree(&count, v); //������ʽ������
            break;

        case 2:
            T = CreateTree(&count, v); //������ʽ������
            arrangement = arrange(count); //�õ�����
            v[0][count + 1] = '*';
            calculate(T, arrangement, count, v); //����
            break;

        case 3:

            printf("������������ݵ�������\n");
            scanf("%d", &r);
            printf("�������¼�˳��������٣��� '0',�� '1'��\n");
            printf("˳��Ϊ:\n");
            c = getchar(); //���ջس�

            for(j = 1; j <= count; j++)
                printf("%c", v[0][j]);

            printf("\n������(�м䲻�ɿո�����������ûس�)");

            for(i = 1; i <= r; i++)
                for(j = 1; j <= count; j++) {
                    scanf("%c", &v[i][j]);
                }//�����ַ�

            v[0][count + 1] = '*'; //��*����ʾ���

            for(i = 1; i <= r; i++)
                calculation(&T, v, i, count);

            printf("�Ƿ��ӡ��ֵ������1��ӡ ����ֵ����ӡ\n");
            scanf("%d", &x);

            if(x == 1)
                printf("��ӡ����ֵ�����£���'*'��������\n");

            for(i = 0; i <= r; i++) {
                for(j = 0; j <= count + 1; j++) {
                    if(x == 1)
                        printf("%c  ", v[i][j]);

                    if(j == count + 1) {
                        if(v[i][j] == '1')
                            b++;

                        if(v[i][j] == '0')
                            b--;
                    }
                }

                if(x == 1)
                    printf("\n");//��ӡ��ֵ��
            }

            if(b == r)
                printf("True forever");
            else if(b * (-1) == r)
                printf("False forever");
            else
                printf("Satisfactible");

            break;  //����жϽ��

        case 0:
            break;

        default:
            printf("�������\n");


        }

        if(k == 0)
            break;

        printf("\n");
        DestroyTree(&T);
        count = 0;
        system("pause");
        system("cls");

    }

    return 0;
}
/****����Ϊ����������****/
void InitQuene(Quene *Q) {
    QNode *p;
    (*Q).front = (*Q).rear = p = (QNode*)malloc(sizeof(QNode));
    (*Q).rear->next = NULL;
}
/****���г�ʼ��*****/
void EnQuene(Quene *Q, TREE* a) {
    QNode *p;
    p = (QNode*)malloc(sizeof(QNode));
    p->next = (*Q).rear->next;
    (*Q).rear->next = p;
    p->data = a;
    (*Q).rear = p;
}
/****���*****/
TREE* DeQuene(Quene *Q) {
    QNode *p;
    TREE* z;

    if(Q->front == Q->rear)
        return NULL;
    else {
        p = (*Q).front->next;
        z = p->data;
        (*Q).front = p;

        if(Q->rear == Q->front)
            Q->rear = Q->front;

        return z;
    }

}
/*****����*****/
/****����Ϊ���еĻ�������****/
void InitS(S *S) {
    (*S).base = (TREE*)malloc(SIZE * sizeof(TREE));
    (*S).top = (*S).base;
    (*S).S_Size = SIZE;
}
/*****ջ�ĳ�ʼ��*****/
void push(S *S, TREE a) {
    *(S->top) = a;
    (S->top)++;
}
/****��ջ****/
TREE pop(S *S) {
    (S->top)--;
    return *(S->top);
}
/****��ջ****/
TREE gettop(S S) {

    return *(--S.top);
}
/****ȡջ��Ԫ��****/
int stackempty(S S) {
    if(S.base != S.top)
        return 0;
    else
        return 1;
}
/*****�жϿ�ջ*****/
/****����Ϊջ�Ļ�������****/
TREE CreateTree_0and1(int count) {
    TREE *T, *q;
    Quene Q;
    int countg;
    T = (TREE*)malloc(sizeof(TREE));
    q = (TREE*)malloc(sizeof(TREE));
    T->data = '_';
    InitQuene(&Q);
    EnQuene(&Q, T);
    //��ʼ��
    countg = pow(2, count) - 1; //Ϊ����Ҫ��ӵĸ���

    for(; countg > 0; countg--) {
        q = DeQuene(&Q);
        q->lchild = (TREE*)malloc(sizeof(TREE));
        q->lchild->data = '0';
        q->rchild = (TREE*)malloc(sizeof(TREE));
        q->rchild->data = '1'; //��ֵ
        EnQuene(&Q, q->lchild);
        EnQuene(&Q, q->rchild);
    }

    for(;;) {
        if((q = DeQuene(&Q)) != NULL) {
            q->lchild = NULL;
            q->rchild = NULL;
        }//�����һ�Ž��з��
        else
            break;

    }

    return *T;
}
/*****����0,1��(��������)*****/
void Visit(TREE *T, char*q, char *p, int *k, int *j) {
    if(T != NULL) {
        int i;
        (*k)++;
        p[(*k)] = T->data;

        if(T->lchild == NULL && T->rchild == NULL) { //�ж��Ƿ���������
            for(i = 0; i <= (*k); i++) {
                q[(*j)] = p[i]; //���������������������
                (*j)++;
            }
        }

        Visit(T->lchild, q, p, k, j);
        Visit(T->rchild, q, p, k, j);
        (*k)--;//��ȥ�Ѿ���ӡ����Ҷ�ӽڵ�
    }


}
/****�Ӹ��ڵ㵽Ҷ�ӽڵ�ı���****/
void get(TREE T, int count, char*q) {
    int i, j = 0;
    int k = -1; //������¼�ַ���ŵ�λ��
    char a[count + 1];
    Visit(&T, q, a, &k, &j); //�Ӹ��ڵ㵽Ҷ�ӽڵ�ı���
    q[j] = '\0'; //����¼���е������һ����������

}
/****�õ�����****/
char* arrange(int count) {
    TREE T;
    char arrangement[SIZE * SIZE]; //������¼��������
    T = CreateTree_0and1(count); //����0����1������������
    get(T, count, arrangement); //���У����õ�����
    return arrangement;
}
/****����****/
/****����Ϊ���в���****/
void DestroyTree(TREE *T) {
    if(T != NULL) {
        DestroyTree(T->lchild);
        DestroyTree(T->rchild);
        free(T);
    }
}
/****��������****/
char cmp(char a, char b) {
    int i, j;
    char Relationship[7][7] = {        //�����ȹ�ϵ�����ɶ�ά���飬����Ѱ�����ȹ�ϵ
        ' ', '|', '&', '~', '(', ')', '#',
        '|', '>', '>', '<', '>', '>', '>',
        '&', '>', '>', '<', '>', '>', '>',
        '~', '>', '>', '>', '>', '>', '>',
        '(', '>', '>', '>', '>', ' ', '>',
        ')', '<', '<', '<', '=', ' ', ' ',
        '#', '<', '<', '<', '<', ' ', '='

    };

    for(i = 1; i < 7; i++) {
        if(Relationship[i][0] == a) {
            break;
        }
    }

    for(j = 1; j < 7; j++) {
        if(Relationship[0][j] == b) {
            break;
        }
    }

    return Relationship[i][j];//���ع�ϵ����

}
/****�Ƚ�****/
TREE CreateTree(int *count, char v[][SIZE]) {
    TREE T;
    char str[50], d; //�����ַ�
    int i, j = 1;
    S Svariable;
    S Soperator;
    InitS(&Svariable);
    InitS(&Soperator);
    TREE *t, *a, *b, *c;
    printf("�������߼����ʽ�������á�|�������ҡ��á�&���������á�~��,��������,'#'������\n");
    printf("��ֻ����6�����ڵ��໥�������¼���\n");
    d = getchar(); //���յ��س�
    gets(str);
    T.data = '#';
    push(&Soperator, T); //�����ʼ����

    for(i = 0; !stackempty(Soperator);) {
        if(str[i] == '#' || str[i] == '|' || str[i] == '&' || str[i] == '~' || str[i] == '(' || str[i] == ')') { //��������Ƚ��д���
            T = gettop(Soperator);
            d = cmp(str[i], T.data); //�Ƚ����ȼ�

            switch(d) {
            case '>'://���ȼ���Ľ�������ѹջ
                t = (TREE*)malloc(sizeof(TREE));
                t->data = str[i];
                t->lchild = NULL;
                t->rchild = NULL;
                push(&Soperator, *t);
                i++;
                break;

            case '='://�����ȥ

                pop(&Soperator);
                i++;
                break;

            case '<'://С�Ľ��е�ջ������������ٽ���ѹջ
                a = (TREE*)malloc(sizeof(TREE));
                b = (TREE*)malloc(sizeof(TREE));
                c = (TREE*)malloc(sizeof(TREE));
                *a = pop(&Soperator);
                *b = pop(&Svariable);
                a->lchild = b;

                if(a->data != '~') {
                    *c = pop(&Svariable);
                    a->rchild = c;
                }

                push(&Svariable, *a);
                break;
            }
        } else if(str[i] >= 'A' && str[i] <= 'Z') { //����ĸ���д���
            v[0][j] = str[i];
            j++;
            t = (TREE*)malloc(sizeof(TREE));
            t->data = str[i];
            t->lchild = NULL;
            t->rchild = NULL;
            push(&Svariable, *t); //����ַѹջ
            i++;
            (*count)++;
        } else {
            printf("�������");
            exit(0);
        }

    }

    return  pop(&Svariable);


}
/****�������ʽ������****/
/****����Ϊ�������ʽ����������****/
char operate(TREE *T) {
    if(T->rchild != NULL && T->lchild != NULL) { //�ж��Ƿ�Ϊ'~'
        //�ж���������
        if(T->lchild->info >= '0' && T->lchild->info <= '1') {
            if(T->rchild->info >= '0' && T->rchild->info <= '1') {
                if(T->data == '|') { //��'|'�Ĵ���
                    if(T->lchild->info == '1' || T->rchild->info == '1')
                        return '1';
                    else
                        return '0';
                } else { //��'&'�Ĵ���

                    if(T->lchild->info == '1' && T->rchild->info == '1')
                        return '1';
                    else
                        return '0';
                }
            }//�������ж�
            else return T->info;
        }//�������ж�

        else
            return T->info;
    } else {
        if(T->lchild != NULL) {
            if(T->lchild->info == '1')
                return '0';

            if(T->lchild->info == '0')
                return '1';

        } else
            return T->info;
    }
}
/***�������***/
void calculation(TREE *T, char(*q)[][SIZE], int i, int count) {
    if(T != NULL) {
        int j;
        calculation(T->lchild, q, i, count);
        calculation(T->rchild, q, i, count);

        if(T->data >= 'A' && T->data <= 'Z') { //�ж��Ƿ�Ϊ�¼�
            for(j = 1; j <= count; j++) {
                if(T->data == (*q)[0][j])
                    T->info = (*q)[i][j]; //Ϊ�¼���ֵ
            }
        } else {
            T->info = operate(T); //���������

            if(T->info == '0' || T->info == '1')
                (*q)[i][count + 1] = T->info; //���������
        }

    }
}
/*****���㣨����******/
void calculate(TREE T, char *q, int count, char v[][SIZE]) {
    int i, j, k = 0, x; //x����������ֵ��

    for(i = 1; i <= pow(2, count); i++) { //�ܿ��ܣ�һһ��ֵ
        for(j = 0; j <= count; j++) {
            v[i][j] = q[k]; //��һά���л�Ϊ��ά
            k++;//һά�ַ����ı���
        }

        calculation(&T, v, i, count); //�����ֿ��ܽ��и�ֵ����
    }

    printf("�Ƿ��ӡ��ֵ������1��ӡ ����ֵ����ӡ\n");
    scanf("%d", &x);

    if(x == 1) {
        printf("��ӡ����ֵ�����£���'*'��������\n");
    }

    k = 0; //������¼'1','0'

    for(i = 0; i <= pow(2, count); i++) {
        for(j = 0; j <= count + 1; j++) {
            if(x == 1) {
                printf("%c ", v[i][j]);
            }

            if(j == count + 1) {
                if(v[i][count + 1] == '1')
                    k++;

                if(v[i][j] == '0')
                    k--;        //����0���͡�1���ĸ���
            }
        }

        if(x == 1)
            printf("\n");
    }

    if(k == pow(2, count)) //���ݡ�0����1�����������Ӧ�Ľ��
        printf("True forever");
    else if(k * (-1) == pow(2, count))
        printf("False forever");
    else
        printf("Satisfactible");

}
/****��ֵ����****/
/****����Ϊ���㲿��****/

