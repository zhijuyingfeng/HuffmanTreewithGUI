#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <queue>
#include <functional>
#include <vector>
#include <QString>
#include <QDebug>
#include <cstdio>

namespace Ui {
class MainWindow;
}

const int Max = 1000003;//一行中可能的最大字符数
const int maxn = 56;//字符集字符个数
const int buffer_size = 4096;//定义缓冲区大小

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_show_huffman_tree_clicked();

private:
    Ui::MainWindow *ui;



    enum TAG { L, R };
    struct TreeNode
    {
        int parent;//父节点在数组中的位置
        TAG tag;//判断该节点为父节点的左儿子还是右儿子
        char path[maxn];//定义编码（0，1）
        int weight;//该节点的权重
        int pos;//节点自身在数组中的位置
        TreeNode();//默认构造函数
        int LeftChild;//左儿子在数组中的位置
        int RightChild;//右儿子所在位置
    };

    class cmp//用于优先队列（堆）的排序
    {
    public:
        bool operator() (const TreeNode & a, const TreeNode& b)
        {
            return a.weight > b.weight;//权重最小的节点位于堆的最前面
        }
    };


    int weight[maxn];//各个字符出现的次数
    int TotalCharNum ;//存储明文中字符的个数
    int CipherCharNum ;//存储密文中用到的字符数
    char charset[maxn];//存储字符集
    char directory[40]="/home/nigao/Documents/HuffmanTree/";

    TreeNode arr[(maxn<<1)-1];

 public:

    void Init();//初始化
    void GenerateHuffmanTree();//产生哈夫曼树
    void encode();//加密
    void SetCharset();//构建字符集
    void GenerateClearText();//生成明文文件
    void GenerateCipherText();//由给出的明文及哈弗曼编码生成密文文件
    int GetCharPos(const char& ch);//获取某个字符在字符集中的位置
    void decode();//将密文转为明文
    char Bin2Char(const bool *arr);//将8位bool值转换为一个char
    void Char2Bin(char ch, bool* arr);//将一个char转换为8位的数组
    char GetPosChar(const int&pos);//获取某个位置上的字符
    void CreateVisual();//Create visual tree
    void tree_create_dot(int pos,FILE* stream);//draw tree nodes recursively
    void Compare();//Compare the difference between clear text and decoded cipher text
    void ShowDecodeText();
//    void ComputeRate();//Compute the compressed rate
//    void ShowHuffmanCoding();

};

#endif // MAINWINDOW_H
