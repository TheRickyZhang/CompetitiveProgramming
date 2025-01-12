// Note: my submission from past when I had different coding style
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int numIslands = 0;
        for(int y = 0; y < grid.size(); ++y) {
            for(int x = 0; x < grid[0].size(); ++x) {
                if(grid[y][x] == '1') {
                    floodFill(grid, y, x, grid.size(), grid[0].size());
                    numIslands++;
                }
            }
        }
        return numIslands;
    }
    void floodFill(vector<vector<char>>& grid, int y, int x, int maxY, int maxX) {
        if(y < 0 || y >= maxY || x < 0 || x >= maxX || grid[y][x] != '1') {
            return;
        }
        grid[y][x] = 'x';
        floodFill(grid, y+1, x, maxY, maxX);
        floodFill(grid, y-1, x, maxY, maxX);
        floodFill(grid, y, x+1, maxY, maxX);
        floodFill(grid, y, x-1, maxY, maxX);
    }
};