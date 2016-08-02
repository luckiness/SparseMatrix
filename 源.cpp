//ϡ������ѹ���洢
#include<iostream>
#include<vector>
using namespace std;
template<typename T>
//ϡ�������Ԫ������͵Ķ���
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
//ϡ�����
class SpareMatrix
{
public:
	
	SpareMatrix()
		:_rowsize(0)
		,_colsize(0)
		,_invalid(0)
	{}
	//����Ԫ���ʾʵ��ϡ������ѹ���洢
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
	//ϡ������ת��
	SpareMatrix<T> Transport()
	{
      SpareMatrix<T> tmp;
	  tmp._rowsize = _colsize;
	  tmp._colsize = _rowsize;
	  tmp._invalid=_invalid;
	  //�������õ��������󿪱ٿռ�,���ǲ��ı�size�Ĵ�С�����ٺ��ʼ����ֵΪԭ���ġ�
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
	//ϡ�����Ŀ���ת��
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
	 
	  //�����ת�þ���ÿһ�з���Ԫ�صĸ���
	  while(index<_a.size())
	  {
	  rowcounts[_a[index]._col]++;
	  index++;
	  }
	

	//�����ת�þ���ÿһ�е�һ������Ԫ������Ԫ����е�λ��
	rowstart[0]=0;
	for(size_t i=1;i<_colsize;i++)
	{
	rowstart[i]=rowstart[i-1]+rowcounts[i-1];
	}

	index=0;
	//��_a���������󿪱�_a��С�Ŀռ�
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
