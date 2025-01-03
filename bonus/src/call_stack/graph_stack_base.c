/*
** EPITECH PROJECT, 2024
** bonus
** File description:
** graph_stack_base
*/

#include "call_graph.h"
#include <string.h>
#include <stdlib.h>

fct_graph_t *fct_graph_manager(void)
{
    static fct_graph_t fct_graph;

    return &fct_graph;
}

void ftrace_graph_init(void)
{
    fct_graph_t *fct_graph = fct_graph_manager();

    fct_graph->current_call = NULL;
    memset(fct_graph->all_node, 0, sizeof(fct_graph->all_node));
}

static void destroy_column(size_t indx)
{
    fct_graph_node_t *tmp;
    fct_child_name_list_t *tmp_childs;
    fct_graph_t *graph = fct_graph_manager();

    while (graph->all_node[indx] != NULL) {
        tmp = graph->all_node[indx];
        graph->all_node[indx] = graph->all_node[indx]->next;
        while (tmp->child != NULL) {
            tmp_childs = tmp->child;
            tmp->child = tmp->child->next;
            free(tmp_childs->name);
            free(tmp_childs);
        }
        free(tmp->file);
        free(tmp->name);
        free(tmp);
    }
    free(graph->current_call);
}

void ftrace_graph_quit(void)
{
    fct_graph_t *fct_graph = fct_graph_manager();

    if (fct_graph->current_call != NULL) {
        free(fct_graph->current_call);
    }
    fct_graph->current_call = NULL;
    for (size_t i = 0; i < GRAPH_LIST_SIZE; ++i) {
        destroy_column(i);
    }
    memset(fct_graph->all_node, 0, sizeof(fct_graph->all_node));
}

size_t hash(char const *str)
{
    size_t hash = 0;

    if (str == NULL) {
        return 0;
    }
    for (size_t i = 0; str[i] != '\0'; ++i) {
        hash = hash * 37 + str[i];
    }
    hash = hash % GRAPH_LIST_SIZE;
    return hash;
}
