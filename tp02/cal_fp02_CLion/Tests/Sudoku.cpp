/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lanca excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}


#include <set>
/**
 * Resolve o Sudoku.
 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
 */
bool Sudoku::solve(){
    if(isComplete()) return true;

    int x = 0, y = 0; set<int> m = {};{
        set<int> cols[9], rows[9], blocks[3][3];
        for(int r = 0; r < 9; ++r){
            for(int c = 0; c < 9; ++c){
                rows[r].insert(numbers[r][c]);
                cols[c].insert(numbers[r][c]);
                blocks[r/3][c/3].insert(numbers[r][c]);
            }
        }
        for(int r = 0; r < 9; ++r){
            for(int c = 0; c < 9; ++c){
                if(numbers[r][c] != 0) continue;
                set<int> s;
                s.insert(rows[r].begin(), rows[r].end());
                s.insert(cols[c].begin(), cols[c].end());
                s.insert(blocks[r/3][c/3].begin(), blocks[r/3][c/3].end());
                if(s.size() > m.size()){
                    x = r;
                    y = c;
                    m = s;
                }
            }
        }
    }
    for(int i = 1; i <= 9; ++i) {
        if (m.count(i) == 0) {
            numbers[x][y] = i;
            ++countFilled;
            if(solve()) return true;
            else{
                numbers[x][y] = 0;
                --countFilled;
            }
        }
    }
	return false;
}



/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
