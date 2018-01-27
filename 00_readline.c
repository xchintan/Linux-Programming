#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<wordexp.h>


int get_input_onehsot() {
	char *input=NULL;
	int i=0;
	int ret;
	wordexp_t tokens;

	input = readline(NULL);
	ret = wordexp(input,&tokens,0);
	i=0;
	while(i < tokens.we_wordc) {
		printf("Token[%d] = %s \n", i, tokens.we_wordv[i]);
		i++;
	}
	wordfree(&tokens);
	free(input);
	return 0;
}
int get_input() {
	char *input=NULL;
	int i=0;
	int ret;
	wordexp_t tokens;
	while(input = readline("#")) {
		ret = wordexp(input,&tokens,0);
		i=0;
		while(i < tokens.we_wordc) {
			printf("Token[%d] = %s \n", i, tokens.we_wordv[i]);
			i++;
		}
		wordfree(&tokens);
		free(input);
	}
	return 0;
}
int main()
{
	int ret =0;
	ret = get_input_onehsot();
	return ret;
}


