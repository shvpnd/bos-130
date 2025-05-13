#include "fs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// actual root object
static FileNode root_node = {
    .name = "/",
    .is_directory = 1,
    .parent = NULL,
    .child_count = 0};

// global pointers
FileNode *root = &root_node;
FileNode *current_dir = &root_node;

void fs_list(FileNode *dir)
{
    for (int i = 0; i < dir->child_count; i++)
    {
        FileNode *child = dir->children[i];
        printf("%s%s\n", child->name, child->is_directory ? "/" : "");
    }
}

void fs_mkdir(const char *name)
{
    if (current_dir->child_count >= 10)
        return;

    FileNode *child = (FileNode *)malloc(sizeof(FileNode));
    strcpy(child->name, name);
    child->is_directory = 1;
    child->parent = current_dir;
    child->child_count = 0;

    current_dir->children[current_dir->child_count++] = child;
}

void fs_create(const char *name)
{
    if (current_dir->child_count >= 10)
        return;

    FileNode *child = (FileNode *)malloc(sizeof(FileNode));
    strcpy(child->name, name);
    child->is_directory = 0;
    child->parent = current_dir;
    child->content[0] = '\0';

    current_dir->children[current_dir->child_count++] = child;
}

void fs_write(const char *name, const char *text)
{
    FileNode *node = find_node(current_dir, name);
    if (node && !node->is_directory)
    {
        strncpy(node->content, text, sizeof(node->content) - 1);
    }
}

const char *fs_read(const char *name)
{
    FileNode *node = find_node(current_dir, name);
    if (node && !node->is_directory)
    {
        return node->content;
    }
    return NULL;
}

void fs_cd(const char *name)
{
    if (strcmp(name, "..") == 0 && current_dir->parent)
    {
        current_dir = current_dir->parent;
        return;
    }

    FileNode *node = find_node(current_dir, name);
    if (node && node->is_directory)
    {
        current_dir = node;
    }
}

void fs_tree(FileNode *dir, int depth)
{
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("%s%s\n", dir->name, dir->is_directory ? "/" : "");

    for (int i = 0; i < dir->child_count; i++)
    {
        fs_tree(dir->children[i], depth + 1);
    }
}

FileNode *find_node(FileNode *dir, const char *name)
{
    for (int i = 0; i < dir->child_count; i++)
    {
        if (strcmp(dir->children[i]->name, name) == 0)
        {
            return dir->children[i];
        }
    }
    return NULL;
}

void get_path(FileNode *node, char *buffer)
{
    if (node->parent == NULL)
    {
        strcpy(buffer, "/");
    }
    else
    {
        char temp[128];
        get_path(node->parent, temp);
        sprintf(buffer, "%s/%s", temp, node->name);
    }
}

void count_nodes(FileNode *node, int *file_count, int *dir_count)
{
    for (int i = 0; i < node->child_count; i++)
    {
        FileNode *child = node->children[i];
        if (child->is_directory)
        {
            (*dir_count)++;
            count_nodes(child, file_count, dir_count);
        }
        else
        {
            (*file_count)++;
        }
    }
}
