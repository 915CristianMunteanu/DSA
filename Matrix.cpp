#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->number_of_columns = nrCols;
	this->number_of_lines = nrLines;
	this->cols = new TElem[this->number_of_columns + 1];
	this->length_of_cols = 0;
	for (int i = 0; i < this->number_of_columns + 1; i++)
		this->cols[i] = 0;
	this->length_of_lines = 0;
	this->capacity_of_lines = 10;
	this->lines = new TElem[this->capacity_of_lines];
	this->values = new TElem[this->capacity_of_lines];
	
}


int Matrix::nrLines() const {
	/// <summary>
	/// The complexity of this one is Theta(1)
	/// </summary>
	/// <returns></returns>
	return this->number_of_lines;
}


int Matrix::nrColumns() const {
	/// <summary>
	/// The complexity of this one is Theta(1)
	/// </summary>
	/// <returns></returns>
	return this->number_of_columns;
}


TElem Matrix::element(int i, int j) const {
	/// <summary>
	/// Best Case:If the (i,j) is not a valid pair, then the complexity is Theta(1).
	/// Average Case:m=number of non-zero elements on that certain column
	///				The for loop is executed m times.
	/// So the complexity should be Theta(m). m being the number of non-zero elements on the column.
	/// In the worst case, the complexity is Theta(this->number_of_lines).
	/// </summary>
	/// <param name="i"></param>
	/// <param name="j"></param>
	/// <returns></returns>
	if (i < 0 || j < 0 || i >= this->number_of_lines || j >= this->number_of_columns)
		throw exception();
	else {
		for (int aux = this->cols[j]; aux < this->cols[j + 1]; aux++)
			if (lines[aux] == i)
				return this->values[aux];
	}
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	/// <summary>
	/// We have more cases:
	/// 1. The (i,j) pair is not valid so Theta(1). Best Case
	/// 2. The (i,j) pair is valid and the value is a non-null value so there will be the complexity from the method - element.
	/// 3. The (i,j) pair is valid but the value is NULL_TELEM.
	/// We have more cases: BEST CASE: We want to add on the last column. The first loop is executed only 1 time.
	///																	  The second loop is executed the number of times of non-zero elements on the column j+1.
	///																	  So in this case we have: Theta(1)+Theta(this->cols[j+1]);
	///						AVERAGE CASE: We want to add on the j column. The first loop is executed (number_of_columns - j) times.
	///																	  The second loop is executed the number of times of non-zero elements on the columns:from the last column untill the j+1 column.
	///																	  So in this case we have: Theta(number_of_columns-j)+Theta(cols[number_of_columns])+Theta(cols[number_of_columns-1])+...+Theta(cols[j+1]);
	///						WORST CASE: We want to add on the first column. First loop is executed (number_of_columns) times.
	///																	  The second loop is executed the number of times of non-zero elements on all columns except from the first one.
	///                                                                   So we have: Theta(number_of_columns)+Theta(cols[number_of_columns])+...+Theta(cols[1]).
	/// </summary>
	/// <param name="i"></param>
	/// <param name="j"></param>
	/// <param name="e"></param>
	/// <returns></returns>
	if (i < 0 || j < 0 || i >= this->number_of_lines || j >= this->number_of_columns)
		throw exception();
	else
	{
		TElem last_value = element(i, j);
		if (last_value != NULL_TELEM)
			for (int aux = this->cols[j]; aux < this->cols[j + 1]; aux++)
				if (lines[aux] == i)
					this->values[aux] = e;
		if (last_value == NULL_TELEM) {
			if (this->length_of_lines == this->capacity_of_lines)
				this->resize();
			for (int it = j + 1; it <= this->number_of_columns + 1; it++)
			{
				this->cols[it] = this->cols[it] + 1;

			}
			this->length_of_lines++;

			for (int it = this->length_of_lines - 1; it >= this->cols[j + 1]; it--)
			{
				this->lines[it] = this->lines[it - 1];
				this->values[it] = this->values[it - 1];
			}

			this->lines[this->cols[j + 1] - 1] = i;
			this->values[this->cols[j + 1] - 1] = e;

		}
		return last_value;
	}
}
	

void Matrix::resize()
{
	this->capacity_of_lines *= 2;
	TElem* new_lines = new TElem[this->capacity_of_lines];
	TElem* new_values = new TElem[this->capacity_of_lines];
	for (int i = 0; i < this->length_of_lines; i++)
	{
		new_lines[i] = this->lines[i];
		new_values[i] = this->values[i];
	}
	delete[] this->lines;
	delete[] this->values;
	this->lines = new_lines;
	this->values = new_values;
}

void Matrix::setMainDiagonal(TElem elem)
{
	/// <summary>
	/// There is no worst case, average case, best case.
	/// The complexity is Theta(number_of_lines)*Theta(number_of_columns).
	/// </summary>
	/// <param name="elem"></param>
	if (this->number_of_lines != this->number_of_columns)
		throw exception();
	for (int i = 0; i < this->number_of_lines; i++)
		for (int j = 0; j < this->number_of_columns; j++)
			if (i == j)
				this->modify(i, j, elem);
}


