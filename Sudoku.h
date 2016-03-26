//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| ^_^ |)
//                      0\  0  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永無bug
//
//***************************************************

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
    int flag; //判斷是否有多組解
	int size;
	int rowof[9*9*9*9*9*4+100]; //紀錄屬於哪一列
	int exist[9*9*9+10]; //紀錄input題目已確定的數字位置
	struct DLX_node{
		int U,D,L,R; //上下左右指標 
		int num; //num存該column object中有多少個 1
		int colobj; //colobj存放開節點所屬之column object編號
	};
	DLX_node dlx[9*9*9*9*9*4+100]; //所有0-1矩陣節點
    int head; //指向整個矩陣的開頭 
	int h[9*9*9+10]; //
	int ans[500];
	void initialization();
    void remove(int col);
	void resume(int col);
	int dfs(int time); //成功傳回1，失敗傳回0，已有多組解傳回2
	void insert(int row, int col); //插入稀疏矩陣'1'節點
};  
