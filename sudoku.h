
class Sudoku{
  public:
    void giveQuestion();
    void readIn();
    void solve();
    void changeNum(int a, int b);
    void changeRow(int a, int b);
    void changeCol(int a, int b);
    void rotate(int n);
    void flip(int n);
    void transform();

  private:
	int map[81];
    int size;
	int x[9*9*9*9*9*4];
	int v[9*9*9];
	struct DLX_node{
		int U,D,L,R; //上下左右指標 
		int num; //num存該column object中有多少個 1
		int colobj; //colobj存放開節點所屬之column object編號
	};
	DLX_node dlx[9*9*9*9*9*4]; //所有0-1矩陣節點
    int head; //指向整個矩陣的開頭 
	int h[9*9*9]; //
	int ans[81];
	void initialization();
    void remove(int col);
	void resume(int col);
	bool dfs(int time);
	void insert(int row, int col);
};  
