#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
#include <string.h>
#include <math.h>
typedef struct TREE {
    char data;//存放字母
    char info;//存放字母的赋值
    struct TREE *lchild;
    struct TREE *rchild;
} TREE;
/*****二叉树的定义*****/
typedef struct {
    TREE *top;
    TREE *base;
    int S_Size;
} S;
/****栈的定义****/

typedef struct QNode {
    TREE *data;
    struct QNode *next;
} QNode;
typedef struct Quene {
    QNode *front;
    QNode *rear;
} Quene;
/*****队列定义*****/
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
/*****以上为函数声明*****/
int main() {

    TREE T;
    int count = 0; //代表事件个数
    char *arrangement;//记录排列结果的指针
    char v[SIZE][SIZE];//真值表
    int k = 10; //菜单选项
    int i, j; //用来标记真值表位置
    char c;//接收无用字符
    int b = 0; //用来数'0','1'
    int r = 1; //常数
    int x;//x用来控制真值表的打印

    for(; k != 0;) {

        printf("请输入您的选择：\n1.输入表达式 \n2.打印真值表并且判断是否为重言式\n3.自己输入赋值并且打印真值表输出对应的结果\n0.退出\n");
        scanf("%d", &k);

        switch(k) {
        case 1:
            T = CreateTree(&count, v); //创造表达式二叉树
            break;

        case 2:
            T = CreateTree(&count, v); //创造表达式二叉树
            arrangement = arrange(count); //得到排列
            v[0][count + 1] = '*';
            calculate(T, arrangement, count, v); //运算
            break;

        case 3:

            printf("请输入测试数据的组数：\n");
            scanf("%d", &r);
            printf("请输入事件顺序输入真假（真 '0',假 '1'）\n");
            printf("顺序为:\n");
            c = getchar(); //吸收回车

            for(j = 1; j <= count; j++)
                printf("%c", v[0][j]);

            printf("\n请输入(中间不可空格隔开，不能用回车)");

            for(i = 1; i <= r; i++)
                for(j = 1; j <= count; j++) {
                    scanf("%c", &v[i][j]);
                }//接收字符

            v[0][count + 1] = '*'; //‘*’表示结果

            for(i = 1; i <= r; i++)
                calculation(&T, v, i, count);

            printf("是否打印真值表：输入1打印 其他值不打印\n");
            scanf("%d", &x);

            if(x == 1)
                printf("打印的真值表如下：（'*'代表结果）\n");

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
                    printf("\n");//打印真值表
            }

            if(b == r)
                printf("True forever");
            else if(b * (-1) == r)
                printf("False forever");
            else
                printf("Satisfactible");

            break;  //输出判断结果

        case 0:
            break;

        default:
            printf("输入错误\n");


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
/****以上为主函数部分****/
void InitQuene(Quene *Q) {
    QNode *p;
    (*Q).front = (*Q).rear = p = (QNode*)malloc(sizeof(QNode));
    (*Q).rear->next = NULL;
}
/****队列初始化*****/
void EnQuene(Quene *Q, TREE* a) {
    QNode *p;
    p = (QNode*)malloc(sizeof(QNode));
    p->next = (*Q).rear->next;
    (*Q).rear->next = p;
    p->data = a;
    (*Q).rear = p;
}
/****入队*****/
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
/*****出队*****/
/****以上为队列的基本操作****/
void InitS(S *S) {
    (*S).base = (TREE*)malloc(SIZE * sizeof(TREE));
    (*S).top = (*S).base;
    (*S).S_Size = SIZE;
}
/*****栈的初始化*****/
void push(S *S, TREE a) {
    *(S->top) = a;
    (S->top)++;
}
/****入栈****/
TREE pop(S *S) {
    (S->top)--;
    return *(S->top);
}
/****出栈****/
TREE gettop(S S) {

    return *(--S.top);
}
/****取栈顶元素****/
int stackempty(S S) {
    if(S.base != S.top)
        return 0;
    else
        return 1;
}
/*****判断空栈*****/
/****以上为栈的基本操作****/
TREE CreateTree_0and1(int count) {
    TREE *T, *q;
    Quene Q;
    int countg;
    T = (TREE*)malloc(sizeof(TREE));
    q = (TREE*)malloc(sizeof(TREE));
    T->data = '_';
    InitQuene(&Q);
    EnQuene(&Q, T);
    //初始化
    countg = pow(2, count) - 1; //为子树要添加的个数

    for(; countg > 0; countg--) {
        q = DeQuene(&Q);
        q->lchild = (TREE*)malloc(sizeof(TREE));
        q->lchild->data = '0';
        q->rchild = (TREE*)malloc(sizeof(TREE));
        q->rchild->data = '1'; //赋值
        EnQuene(&Q, q->lchild);
        EnQuene(&Q, q->rchild);
    }

    for(;;) {
        if((q = DeQuene(&Q)) != NULL) {
            q->lchild = NULL;
            q->rchild = NULL;
        }//对最后一排进行封闭
        else
            break;

    }

    return *T;
}
/*****建立0,1树(用于排列)*****/
void Visit(TREE *T, char*q, char *p, int *k, int *j) {
    if(T != NULL) {
        int i;
        (*k)++;
        p[(*k)] = T->data;

        if(T->lchild == NULL && T->rchild == NULL) { //判断是否遍历到最深处
            for(i = 0; i <= (*k); i++) {
                q[(*j)] = p[i]; //将遍历结果存入其他数组
                (*j)++;
            }
        }

        Visit(T->lchild, q, p, k, j);
        Visit(T->rchild, q, p, k, j);
        (*k)--;//减去已经打印过的叶子节点
    }


}
/****从根节点到叶子节点的遍历****/
void get(TREE T, int count, char*q) {
    int i, j = 0;
    int k = -1; //用来记录字符存放的位置
    char a[count + 1];
    Visit(&T, q, a, &k, &j); //从根节点到叶子节点的遍历
    q[j] = '\0'; //给记录排列的数组加一个结束符号

}
/****得到排列****/
char* arrange(int count) {
    TREE T;
    char arrangement[SIZE * SIZE]; //用来记录排列数据
    T = CreateTree_0and1(count); //创造0——1树来便于排列
    get(T, count, arrangement); //排列，并得到数组
    return arrangement;
}
/****排列****/
/****以上为排列部分****/
void DestroyTree(TREE *T) {
    if(T != NULL) {
        DestroyTree(T->lchild);
        DestroyTree(T->rchild);
        free(T);
    }
}
/****树的销毁****/
char cmp(char a, char b) {
    int i, j;
    char Relationship[7][7] = {        //把优先关系表做成二维数组，从中寻找优先关系
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

    return Relationship[i][j];//返回关系符号

}
/****比较****/
TREE CreateTree(int *count, char v[][SIZE]) {
    TREE T;
    char str[50], d; //接收字符
    int i, j = 1;
    S Svariable;
    S Soperator;
    InitS(&Svariable);
    InitS(&Soperator);
    TREE *t, *a, *b, *c;
    printf("请输入逻辑表达式（‘或’用‘|’，‘且’用‘&’，‘否’用‘~’,允许括号,'#'结束）\n");
    printf("（只接受6个以内的相互独立的事件）\n");
    d = getchar(); //接收掉回车
    gets(str);
    T.data = '#';
    push(&Soperator, T); //填入初始符号

    for(i = 0; !stackempty(Soperator);) {
        if(str[i] == '#' || str[i] == '|' || str[i] == '&' || str[i] == '~' || str[i] == '(' || str[i] == ')') { //对运算符等进行处理
            T = gettop(Soperator);
            d = cmp(str[i], T.data); //比较优先级

            switch(d) {
            case '>'://优先级大的建立子树压栈
                t = (TREE*)malloc(sizeof(TREE));
                t->data = str[i];
                t->lchild = NULL;
                t->rchild = NULL;
                push(&Soperator, *t);
                i++;
                break;

            case '='://相等消去

                pop(&Soperator);
                i++;
                break;

            case '<'://小的进行弹栈，组成新树后再进行压栈
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
        } else if(str[i] >= 'A' && str[i] <= 'Z') { //对字母进行处理
            v[0][j] = str[i];
            j++;
            t = (TREE*)malloc(sizeof(TREE));
            t->data = str[i];
            t->lchild = NULL;
            t->rchild = NULL;
            push(&Svariable, *t); //将地址压栈
            i++;
            (*count)++;
        } else {
            printf("输入错误");
            exit(0);
        }

    }

    return  pop(&Svariable);


}
/****建立表达式二叉树****/
/****以上为创建表达式二叉树部分****/
char operate(TREE *T) {
    if(T->rchild != NULL && T->lchild != NULL) { //判断是否为'~'
        //判断左右子树
        if(T->lchild->info >= '0' && T->lchild->info <= '1') {
            if(T->rchild->info >= '0' && T->rchild->info <= '1') {
                if(T->data == '|') { //对'|'的处理
                    if(T->lchild->info == '1' || T->rchild->info == '1')
                        return '1';
                    else
                        return '0';
                } else { //对'&'的处理

                    if(T->lchild->info == '1' && T->rchild->info == '1')
                        return '1';
                    else
                        return '0';
                }
            }//右子树判断
            else return T->info;
        }//左子树判断

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
/***计算规则***/
void calculation(TREE *T, char(*q)[][SIZE], int i, int count) {
    if(T != NULL) {
        int j;
        calculation(T->lchild, q, i, count);
        calculation(T->rchild, q, i, count);

        if(T->data >= 'A' && T->data <= 'Z') { //判断是否为事件
            for(j = 1; j <= count; j++) {
                if(T->data == (*q)[0][j])
                    T->info = (*q)[i][j]; //为事件赋值
            }
        } else {
            T->info = operate(T); //存入计算结果

            if(T->info == '0' || T->info == '1')
                (*q)[i][count + 1] = T->info; //存入计算结果
        }

    }
}
/*****计算（后序）******/
void calculate(TREE T, char *q, int count, char v[][SIZE]) {
    int i, j, k = 0, x; //x用来控制真值表

    for(i = 1; i <= pow(2, count); i++) { //总可能，一一赋值
        for(j = 0; j <= count; j++) {
            v[i][j] = q[k]; //将一维排列化为二维
            k++;//一维字符串的遍历
        }

        calculation(&T, v, i, count); //对这种可能进行赋值运算
    }

    printf("是否打印真值表：输入1打印 其他值不打印\n");
    scanf("%d", &x);

    if(x == 1) {
        printf("打印的真值表如下：（'*'代表结果）\n");
    }

    k = 0; //用来记录'1','0'

    for(i = 0; i <= pow(2, count); i++) {
        for(j = 0; j <= count + 1; j++) {
            if(x == 1) {
                printf("%c ", v[i][j]);
            }

            if(j == count + 1) {
                if(v[i][count + 1] == '1')
                    k++;

                if(v[i][j] == '0')
                    k--;        //数‘0’和‘1’的个数
            }
        }

        if(x == 1)
            printf("\n");
    }

    if(k == pow(2, count)) //根据‘0’‘1’个数输出对应的结果
        printf("True forever");
    else if(k * (-1) == pow(2, count))
        printf("False forever");
    else
        printf("Satisfactible");

}
/****真值计算****/
/****以上为计算部分****/

