//稀疏矩阵的压缩存储
#include<iostream>
#include<vector>
using namespace std;
template<typename T>
//稀疏矩阵三元组表类型的定义
struct Triple
{
	T _value;
	size_t _row;
	size_t _col;
	
	Triple(size_t row=0,size_t col=0,const T& value=T())
		:_value(value)
		,_row(row)
		,_col(col)
	{}

};
template<typename T>
//稀疏矩阵
class SpareMatrix
{
public:
	
	SpareMatrix()
		:_rowsize(0)
		,_colsize(0)
		,_invalid(0)
	{}
	//用三元组表示实现稀疏矩阵的压缩存储
	SpareMatrix(T* a,size_t m,size_t n,const T& invalid)
		:_rowsize(m)
		,_colsize(n)
		,_invalid(invalid)
	{
		for(size_t i=0;i<m;i++)
		{
			for(size_t j=0;j<n;j++)
			{
				if(a[i*n+j]!=invalid)
				{
				_a.push_back(Triple<T>(i,j,a[i*n+j]));
				}
			}
		}
	
	}
	//稀疏矩阵的转置
	SpareMatrix<T> Transport()
	{
      SpareMatrix<T> tmp;
	  tmp._rowsize = _colsize;
	  tmp._colsize = _rowsize;
	  tmp._invalid=_invalid;
	  //给构建好的匿名对象开辟空间,但是不改变size的大小，开辟后初始化的值为原来的。
	  tmp._a.reserve(_a.size());
	  for(size_t i=0;i<_colsize;i++)
	  {
		  size_t index=0;
		  for(index=0;index<_a.size();index++)
		  {
			   if(_a[index]._col==i)
			   {
			   Triple <T> tp;
			   tp._row=_a[index]._col;
			   tp._col=_a[index]._row;
			   tp._value=_a[index]._value;
			   tmp._a.push_back(tp);
			   }
		  }
	  }
	  return tmp;
	  
	}
	//稀疏矩阵的快速转置
	SpareMatrix<T> FastTransport()
	{
	  SpareMatrix<T> tmp;
	  tmp._rowsize = _colsize;
	  tmp._colsize = _rowsize;
	  tmp._invalid=_invalid;
	  int* rowcounts=new int[tmp._rowsize];
	  int* rowstart=new int[tmp._rowsize];
	  memset(rowcounts,0,sizeof((int*)_colsize));
	  memset(rowstart,0,sizeof((int*)_colsize));
	  size_t index=0;
	 
	  //计算待转置矩阵每一列非零元素的个数
	  while(index<_a.size())
	  {
	  rowcounts[_a[index]._col]++;
	  index++;
	  }
	

	//计算待转置矩阵每一列第一个非零元素在三元组表中的位置
	rowstart[0]=0;
	for(size_t i=1;i<_colsize;i++)
	{
	rowstart[i]=rowstart[i-1]+rowcounts[i-1];
	}

	index=0;
	//给_a的匿名对象开辟_a大小的空间
    tmp._a.resize(_a.size());
	while(index<=_a.size())
	{/*
		size_t rowindex=_a[index]._col;*/
		int& start=rowstart[_a[index]._col];

		Triple<T> tp;
		tp._value=_a[index]._value;
		tp._row=_a[index]._col;
		tp._col=_a[index]._row;
		tmp._a[start++]=tp;
		index++;
	}
	return tmp;
}
	void display()
	{
	   size_t index=0;
		for(size_t i=0;i<_rowsize;i++)
		{
			for(size_t j=0;j<_colsize;j++)
			{
			   if(index<_a.size() && _a[index]._row==i && _a[index]._col==j)
			   {
		        cout<<_a[index++]._value<<" ";
			   }
			   else
			   {
			   cout<<_invalid<<" ";
			   }
			}
			cout<<endl;
		}
		cout<<endl;
	}


protected:
	vector<Triple <T> > _a;
	size_t _rowsize;
	size_t _colsize;
	T _invalid;

};

void test()
{
	    int a[4][4]={{1,0,0,0},
	                 {2,2,0,0},
	                 {0,1,3,0},
	                 {1,0,0,4}};
	SpareMatrix<int>sm1((int*)a,4,4,0);
	sm1.display();

	SpareMatrix<int> sm2=sm1.Transport();
	sm1.display();

	SpareMatrix<int> sm3=sm1.FastTransport();
	sm1.display();
}
int main()
{
	test();
	getchar();
	return 0;
}
