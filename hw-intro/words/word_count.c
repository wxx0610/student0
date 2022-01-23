/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utililties */

char *new_string(char *str) {
    return strcpy((char *) malloc(strlen(str) + 1), str);
}

void init_words(WordCount **wclist) {
    /* Initialize word count.  */
    *wclist = NULL;
}

size_t len_words(WordCount *wchead) {
    size_t len = 0;
    WordCount *wc;
    for (wc = wchead; wc; wc = wc->next) {
        ++len;
    }
    return len;
}

WordCount *find_word(WordCount *wchead, char *word) {
    /* Return count for word, if it exists */
    WordCount *first = wchead;
    while (first != NULL) {
        if (!strcmp(first->word, word)) {//如果两个字符串相同
            return first;
        }
        first = first->next;
    }
    return first;
}

// void wordcount_sort(WordCount **wclist, bool less(const WordCount *, const WordCount *)) {
//     WordCount *p, *q;
//     for (p = *wclist; p != NULL; p = p->next) {
//         for (q = p->next; q != NULL; q = q->next) {
//             if (!less(p, q)) {//如果p > q
//                 char *temp_word = p->word;
//                 int temp_count = p->count;
//                 p->word = q->word;
//                 p->count = q->count;
//                 q->word = temp_word;
//                 q->count = temp_count;
//             }
//         }
//     }
// }

void add_word(WordCount **wclist, char *word) {
    /* If word is present in word_counts list, increment the count, otw insert with count 1. */
    char *data = new_string(word);
    WordCount *target = find_word(*wclist, data);//查找这个单词
    if (target != NULL) {//如果出行过
        ++target->count;
    } else {//如果没有找到相同的单词
        WordCount *node = malloc(sizeof(WordCount));//堆上创建节点
        node->word = data;
        node->count = 1;
        node->next = (*wclist);//在头部插入元素
        *wclist = node;
    }
}

void fprint_words(WordCount *wchead, FILE *ofile) {
    /* print word counts to a file */
    WordCount *wc;
    for (wc = wchead; wc; wc = wc->next) {
        fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
    }
}
