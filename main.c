#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "header/calculate.h"
#include "header/utility.h"
#include "header/translation.h"

//程序入口
int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
	// 四则运算
//	run_calculate();

	// 快译通
	run_translations();

	//pause();
	system("pause");
	return 0;
}
