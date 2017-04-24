#include <stdio.h>
#include <stdlib.h>
struct vect{
    size_t len,flag;
    long long *koef;
    long long num_val;
};
typedef struct vect vec;
size_t mul(vec *first,vec numb)
{
    if (!first)
        return 0;
    if (numb.flag != 1)
        return 0;
    else
        if (first->len < 2)
            return 0;
    else
        {
            for (size_t i = 0;i < first->len;i++)
            {
                if (first->koef + i == NULL)
                    return 0;
                else
                    first->koef[i] *= numb.num_val;
            }
        }
    return 1;
}
size_t add(vec *first,vec *second,char sign)
{
    if (!first || !second)
        return 0;
    if (first->len < 2 || second->len <2 || (sign != '+' && sign != '-'))
    {
        return 0;
    }
    else
    {
        size_t maxlen = first->len > second->len ? first->len : second->len;
        if ( !realloc(first->koef , maxlen * sizeof(long long)))
            return 0;
        if ( !realloc(second->koef, maxlen * sizeof(long long)))
            return 0;
        for (size_t i = 0;i < maxlen; i++)
        {
            if (first->koef+i == NULL || second->koef+i == NULL)
                return 0;
            else {
                if (sign == '+')
                    first->koef[i] += second->koef[i];
                else if (sign == '-')
                    first->koef[i] -= second->koef[i];
                free(second->koef);
            }
        }
        return 1;
    }
}
int main(void)
{
    char ch = '\0';
    char *steck = NULL;
    vec *ans = NULL;
    size_t ans_len = 0;
    size_t steck_len = 0;
    size_t big_error = 0;
    char buff = '\0';
    //while (!scanf("%c",&ch))
    while (buff=='\0' ? !scanf("%c",&ch): ch=buff)
    {
        if (big_error == 1)
            break;
            buff = '\0';
        if (ch == ' ')
            continue;
        else
        if (ch == '(' || ch == '-' || ch == '+' || ch == '*')
        {
            steck_len++;
            if (! realloc(steck,steck_len * sizeof(char)))
            {
                big_error = 1;
                break;
            }
            steck[steck_len - 1]=ch;
        }
/////////////////kekkekkekeke///////////////////////////////////////////////////////////////////
        else
            if (ch==')')
            {
                size_t ff = 0;
                while (steck_len > 0  && steck[steck_len - 1] != ')')
                {
                    if (ans_len <2)
                    {
                        big_error = 1;
                        break;
                    }
                    if (steck[steck_len - 1] == '+' || steck[steck_len - 1] == '-')
                    {
                        if (ans[ans_len - 2].flag == 1 || ans[ans_len -1].flag ==1 )
                        {
                            big_error = 1;
                            break;
                        }
                        if (!add(ans+ans_len - 2,ans+ans_len - 1,steck[steck_len - 1]))
                        {
                            big_error = 1;
                            break;
                        }
                        free(ans+ans_len-1);
                        ans_len--;
                    }
                    else
                        if (steck[steck_len - 1] == '*')
                        {
                            if (ans[ans_len -2].flag + ans[ans_len -1].flag != 1)
                            {
                                big_error = 1;
                                break;
                            }
                            if (ans[ans_len -2].flag == 1)
                            {
                                ans[ans_len -1].flag = 1;
                                ans[ans_len -2].flag = 0;
                                size_t qbuf = ans[ans_len -1].len;
                                ans[ans_len - 1].len = ans[ans_len - 2].len;
                                ans[ans_len - 2].len = qbuf;
                                long long llbuf = ans[ans_len -1].num_val;
                                ans[ans_len - 1].num_val = ans[ans_len - 2].num_val;
                                ans[ans_len - 2].num_val = llbuf;
                                long long *ptrbuff = ans[ans_len -1].koef;
                                ans[ans_len - 1].koef = ans[ans_len - 2].koef;
                                ans[ans_len - 2].koef = ptrbuff;
                            }
                            if (!mul(ans + ans_len - 2,ans[ans_len - 1]))
                            {
                                big_error = 1;
                                break;
                            }
                            free(ans + ans_len - 1);
                            ans_len--;
                        }
                    else
                        {
                            big_error = 1;
                            break;
                        }

                }
                if (big_error)
                    break;
                if (steck_len > 0 && steck[steck_len -1] == '(' )
                {
                    if (!realloc(steck,(steck_len - 2) * sizeof(char)))
                    {
                        big_error = 1;
                        break;
                    }
                }
                else
                {
                    big_error = 1;
                    break;
                }
            }
        else
////////////////////////////////////////////////////////////////////////////////////
            if (ch >= '0' && ch <= '9')
        {
            vec numb;
            numb.flag = 1;
            numb.num_val = (long long)(ch) - (long long)('0');
            while (!scanf("%c",&ch) && ch>='0' && ch<='9')
            {
                numb.num_val *= 10;
                numb.num_val += (long long)(ch) - (long long)('0');
            }
            buff = ch;
            ans_len++;
            if (! realloc(ans,ans_len * sizeof(struct vect)))
            {
                big_error = 1;
                break;
            }
            ans[ans_len - 1]=numb;
        }
///////////////////////////////////////////////////////////////////////////////////
        if (ch == '{')
        {
            ans_len++;
            if (! realloc(ans,ans_len * sizeof(struct vect)))
            {
                big_error = 1;
                break;
            }
            ans[ans_len - 1].flag = 0;
            char f_buf = '\0';
            size_t mode = 0;
            while (f_buf=='\0'?!scanf("%c",&ch) && ch != '}' : ch==f_buf)
            {
                f_buf='\0';
                if (ch == ' ' || ch == ',')
                {
                    mode = 0;
                    continue;
                }
                else
                    if (ch >= '0' && ch <= '9')
                    {
                        if (mode == 1)
                        {
                            big_error = 1;
                            break;
                        }
                        else
                            mode = 1;
                        long long kkoef=(long long)(ch)- (long long)('0');

                        while (!scanf("%c",&ch) && ch>='0' && ch<='9')
                        {
                            kkoef *= 10;
                            kkoef += (long long)(ch)- (long long)('0');
                        }
                        f_buf = ch;

                        ans[ans_len - 1].len++;
                        if (!realloc(ans[ans_len - 1].koef,ans[ans_len - 1].len* sizeof(long long)))
                        {
                            big_error = 1;
                            break;
                        }
                        ans[ans_len -1].koef[ans[ans_len -1].len -1] = kkoef;
                    }
                else
                    {
                        big_error = 1;
                        break;
                    }
                if (big_error = 1)
                    break;
            }
        }
    }

    return 0;
}