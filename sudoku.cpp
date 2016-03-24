#include<stdio.h>
#include"sudoku.h"

void Sudoku::giveQuestion(){
	printf("0 0 0 0 0 5 0 2 0\n");
	printf("1 0 0 9 0 0 0 0 0\n");
	printf("4 0 0 0 0 0 0 0 0\n");
	printf("0 0 8 0 0 2 0 0 0\n");
	printf("0 0 0 0 0 0 0 0 1\n");
	printf("0 0 0 0 0 0 9 0 4\n");
	printf("0 0 5 0 0 0 3 0 0\n");
	printf("0 0 0 1 0 0 0 0 7\n");
	printf("0 0 2 4 0 8 0 0 0\n");
	return;
}

void Sudoku::readIn(){
	int i;
	for(i=0;i<81;i++)
		scanf("%d",&map[i]);
	return;
}

void Sudoku::solve(){

}

void Sudoku::changeNum(int a, int b){

}

void Sudoku::changeRow(int a, int b){

}

void Sudoku::changeCol(int a, int b){

}

void Sudoku::rotate(int n){

}

void Sudoku::flip(int n){

}

void Sudoku::transform(){

}

/*
 * private member function
 */

void Sudoku::initialization(){
	head = 0;
	for(int i=0; i<=9*9*4; i++) //初始化column object的dlx node
	{
		dlx[i].num = 0; //1的個數初始化為0
		dlx[i].U = i; //column object的上下指標初始化指回自己
		dlx[i].D = i;
		dlx[i].R = i+1;//column object的左右指標串起來
		dlx[i].L = i-1;
	}
	size = 9*9*4;
	dlx[9*9*4].R = 0; //最後面的指標拉回指向開頭
	int temp = 9*9*9;
	while(temp>=0)
	{
		h[temp] = -1;
		temp--;
	}
}

void Sudoku::remove(int col){
	/*
	 * 把選定的column object(編號col)移除
	 * 結構是以雙向鏈結儲存，將右邊的指標指向左邊
	 * 再將左邊的指標指向右邊
	 * 同時不真正釋放此節點，此節點之左右指標仍指向原先左右節點
	 * 故可在之後發現錯誤重新連回去
	 */
	dlx[dlx[col].R].L = dlx[col].L;
	dlx[dlx[col].L].R = dlx[col].R;
	int i = dlx[col].D; //i是被選中之column底下的第一個節點
	while(i != col) //如果往下指回自己，表示沒有'1'
	{
		//i現在指向選中之column底下的'1'節點
		int j = dlx[i].R; //j是i所指'1'節點右手邊的'1'節點
		while(j != i)
		{
			/*
			 * 選擇某一個'1'之後，右手邊有'1'皆不可被選
			 * 所以將同一列之所有'1'節點透過相同手法暫時移除
			 */
			dlx[dlx[j].D].U = dlx[j].U;
			dlx[dlx[j].U].D = dlx[j].D;
			dlx[dlx[j].colobj].num --; //該column object少了一個'1'
			j = dlx[j].R; //繼續往右邊找
		}
		i = dlx[i].D; //往下一個'1'節點做一樣的同一列'1'移除
	}
}


void Sudoku::resume(int col){
	/*
	 * 之前雖然被暫時移除了，但其上下左右指標仍存在
	 * 先指向其上方的'1'節點
	 * 因為先前將同列上的'1'節點都暫時移除了
	 * 所以現在由下而上的一一跑過這一column的'1'節點
	 * 去回復同一列的'1'節點之有效性
	 * 回復完之後指回自己的coiumn object再將左右的指標回復
	 */
	int i = dlx[col].U; 
	while(i != col)
	{
		//i指著由下而上的第一個節點
		int j = dlx[i].L;
		while(j != i)
		{
			//j指著欲回復的'1'節點
			dlx[dlx[j].U].D = j;
			dlx[dlx[j].D].U = j;
			dlx[dlx[j].colobj].num ++; //回復之後'1'加回來
			j = dlx[j].L; //繼續往左邊找'1'回復
		}
		i = dlx[i].U; //繼續往上找回復
	}
	//指回自己column object了，將左右指標回復
	dlx[dlx[col].R].L = col;
	dlx[dlx[col].L].R = col;
}

bool Sudoku::dfs(int time){
	if(dlx[head].R == head)   	
	{
	//開頭向右指標指回開頭，表示已經沒有column object可以選擇
	//也就是已經都成功的選擇，即已有解=>輸出
	   for(int i=0; i<time; i++)
	   {
		   map[(x[ans[i]]-1)/9 + 1] = (x[ans[i]]-1)/9 +1;
	   }
	   for(int i=1; i<81; i++)
	   {
		   printf("%d%c",map[1],(i+1)%9==0?'\n':' ');
	   }
	   printf("\n");
	   return true; //有解回傳true
	}
	//以下便為尚有column object可以選擇的情況
	int col;
	int temp = 9999999;
	int i = dlx[head].R; //從第一個開始
	while(i != head)
	{
		if(dlx[i].num < temp)
		{
			temp = dlx[i].num; //即找出擁有'1'最少節點的column object
			col = i; //並記錄下來優先移除，以有效減少branch個數
		}
		i = dlx[i].R; //每一個掃過找最小，直到指回head
	}
	//現在擁有最少'1'個數之column object編號:col
	remove(col);  //暫時移除
	i = dlx[col].D; //i是移除後下方的'1'節點
	while(i != col)
	{
		ans[time] = i;
		int j = dlx[i].R;
		while(j != i)
		{
			remove(dlx[j].colobj); //同一列有'1'之column object就不能選了
			j = dlx[j].R;
		}
		//移除完不能被選擇的選項了
		if(dfs(time+1)) //繼續往下做下一次的dfs
		{
			return true; //若都傳為true，則往上傳回true，表示有解
		}
		//若其中一層false，則為選錯column object
		j = dlx[i].L;
		while(j != i)
		{
			resume(dlx[j].colobj); //剛剛移除的回復
			j = dlx[j].L; //直到都回復
		}
		i = dlx[i].D;
	}
	resume(col); //把這個選錯的column object回復回來
	return false; //傳回上層失敗，跳回上層繼續往下一個試
    //直到最外層也傳回失敗表示無解
}

void Sudoku::insert(int row, int col){
	int temp = ++size; //指向已被使用的size範圍後面下一個
	dlx[temp].colobj = col; //該點隸屬於編號col 的 column object
	dlx[col].num++; //'1'的節點插入多一個
	x[temp] = row;
	dlx[temp].D = dlx[col].D; //輸入時由0~81插入，所以只需將其下指標往上拉回
    dlx[dlx[col].D].U = temp;
	dlx[temp].U = col;
	dlx[col].D = temp;
	if(h[row] < 0)
	{
		h[row] = temp;
		dlx[temp].L = temp;
		dlx[temp].R = temp;
	}
	else
	{
		dlx[temp].R = dlx[h[row]].R;
		dlx[dlx[h[row]].R].L = temp;
		dlx[temp].L = h[row];
		dlx[h[row]].R = temp;
	}
}
	











