/*Copyright (c) Orcon Systems LLc,2023
 * All rights reserved.
 *
 * This source code is licensed under the LGPL license found in the
 * LICENSE file in the root directory of this source tree.
 * No hereby grants to any person obtaining a copy of this software and
 * associated documentation files (the "Software") the rights to use, copy,
 * modify, merge, publish, and distribute copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 * No person or entity shall use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software in source code or binary
 * form, with or without modification, for any purpose.
 * No person or entity shall sell, rent, lease, sublicense, lend, or
 * redistribute the Software, or any modified versions thereof, without
 * explicit permission from Orcon Systems LLc.
 * No person or entity shall use the Software in applications designed to
 * perform safety-critical tasks, such as medical-device applications, unless
 * said person or entity intends to use the Software for such tasks.
 * 
 * No person or entity shall imply or claim that Orcon Systems LLc endorses
 * said person or entity (or any products which said person or entity
 * produces), unless said person or entity has received explicit permission
 * from Orcon Systems LLc.
 * 
 * No person or entity shall use the name of Orcon Systems LLc to endorse or
 * promote products derived from the Software without explicit permission from
 * Orcon Systems LLc.
 * You should have received a copy of the LGPL along with this library.

*/

// Path: src/main.c
// Created by afif on 10/16/2023
#include <stdio.h>
#include <string.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"

#define MAX_LIMIT 20
void print_help()
{
    printf("Usage:\nhello.out <filename>\n");
    exit(1);
}

int main(int argc, char* argv[])
{
    if (argc >= 2){
        for(int i = 1; i < argc; i++){
            int len = strlen(argv[i]);
            char* last_four = &argv[i][len-6];
            if(strcmp(last_four,".orcl") == 0){
                                lexer_T* lexer = init_lexer(
                    get_file_contents(argv[i])
                );
                parser_T* parser = init_parser(lexer);
                AST_T* root = parser_parse(parser, parser->scope);
                visitor_T* visitor = init_visitor();
                visitor_visit(visitor, root);
            }

            else {
                print_help();
            }
        }
    }
    else {
        char input[MAX_LIMIT];
        while(1){
            printf("Welcome to the orclang programming  language v. 0.0.1!\nCreated by Afif_sh\n>>> ");
            fgets(input,MAX_LIMIT, stdin);
            lexer_T* lexer = init_lexer(input);
            parser_T* parser = init_parser(lexer);
            AST_T* root = parser_parse(parser, parser->scope);
            visitor_T* visitor = init_visitor();
            visitor_visit(visitor, root);
        }
    }
    return 0;
}
