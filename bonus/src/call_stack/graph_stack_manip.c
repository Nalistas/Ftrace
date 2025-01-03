/*
** EPITECH PROJECT, 2024
** bonus
** File description:
** graph_stack_manip
*/

#include "call_graph.h"
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void store_new_node(char const *str, char const *file, size_t depth)
{
    fct_graph_t *fct_graph = fct_graph_manager();
    size_t ndx = hash(str);
    fct_graph_node_t *tmp = fct_graph->all_node[ndx];

    while (tmp != NULL && strcmp(tmp->name, str) != 0) {
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        tmp = malloc(sizeof(fct_graph_node_t));
        tmp->name = strdup(str);
        tmp->file = strdup(file);
        tmp->child = NULL;
        tmp->max_depth = depth;
        tmp->next = fct_graph->all_node[ndx];
        fct_graph->all_node[ndx] = tmp;
    }
    if (tmp->max_depth < depth) {
        tmp->max_depth = depth;
    }
}

static void add_child_to_current(char const *str)
{
    fct_graph_t *fct_graph = fct_graph_manager();
    fct_graph_node_t *tmp = fct_graph->all_node[hash(fct_graph->current_call)];
    fct_child_name_list_t *childs = NULL;

    while (tmp != NULL && strcmp(tmp->name, fct_graph->current_call) != 0) {
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return;
    }
    childs = tmp->child;
    tmp->child = malloc(sizeof(fct_child_name_list_t));
    tmp->child->name = strdup(str);
    tmp->child->next = childs;
}

void ftrace_graph_add_new_call(char const *str, char const *file, size_t depth)
{
    store_new_node(str, file, depth);
    add_child_to_current(str);
    ftrace_graph_change_current_call(str);
}

void ftrace_graph_change_current_call(char const *str)
{
    fct_graph_t *fct_graph = fct_graph_manager();

    if (fct_graph == NULL) {
        return;
    }
    if (fct_graph->current_call != NULL) {
        free(fct_graph->current_call);
    }
    fct_graph->current_call = strdup(str);
}

static void display_node(int fd, fct_graph_node_t *node)
{
    dprintf(fd, "<node name=\"%s\" max_depth=\"%lu\" file=\"%s\">\n", node->name,
        node->max_depth, node->file);
    for (fct_child_name_list_t *tmp = node->child; tmp != NULL;
        tmp = tmp->next) {
        dprintf(fd, "<child name=\"%s\"/>\n", tmp->name);
    }
    dprintf(fd, "</node>\n");
}

void ftrace_graph_store_call_graph(void)
{
    fct_graph_t *fct_graph = fct_graph_manager();
    int fd = open("graph.xml", O_WRONLY | O_TRUNC | O_CREAT, 0644);

    if (fd < 0) {
        return;
    }
    dprintf(fd, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    dprintf(fd, "<?xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"?>\n");
    dprintf(fd, "<graph>\n");
    for (size_t i = 0; i < GRAPH_LIST_SIZE; ++i) {
        fct_graph_node_t *tmp = fct_graph->all_node[i];
        while (tmp != NULL) {
            display_node(fd, tmp);
            tmp = tmp->next;
        }
    }
    dprintf(fd, "</graph>\n");
    close(fd);
}
