#ifndef RANDOMDECISSIONTREE_H_INCLUDED
#define RANDOMDECISSIONTREE_H_INCLUDED

#include <bits/stdc++.h>
#include <vector>
using namespace std;


#define MAX 30
#define COL 7
#define MAX_DATA 40
//#define START 100

struct row_info
{
    int matchId;
    string attribute_Info[4];
    double numericAttribute_Info[7];
    string winner;

};

row_info values[MAX_DATA], all_values[MAX_DATA];
int rand_col[5][42] = {0}, tree_index = 0;
double Thresold;

struct node
{
    int attribute_number, child_number;
    string class_name, internal_class_name;
    double Thresold;
    double thresold[7];
    int level;
    bool leaf = false;
    node **child;
    vector<row_info> row;
};


void calculate_gain_value(node *row_information);
void addChildren(node *children);




void load_data(int seed)
{
    for (int i = 0; i < MAX_DATA; i++)
    {

        values[i].matchId = all_values[i].matchId ;
        for(int j=0;j<4;j++)
            values[i].attribute_Info[j] = all_values[i].attribute_Info[j];
        for(int j=4;j<7;j++){
            values[i].numericAttribute_Info[j] = all_values[i].numericAttribute_Info[j];
        }
        values[i].winner = all_values[i].winner;
    }
}

void load_all_data()
{
    char temp;
    int a, b, c;
    ifstream myFile("new.txt");
    for (int i = 0; i < MAX_DATA; i++)
    {   myFile >> all_values[i].matchId;
        for(int j=0;j<4;j++){
            myFile >> all_values[i].attribute_Info[j];
        }
        for(int j=4;j<7;j++)
            myFile >> all_values[i].numericAttribute_Info[j];
        myFile >> all_values[i].winner;
    }
}


struct node *create_tree()
{
    node *root = new node();
    root->leaf = false;
    for (int i = 0; i < MAX; i++)
    {
        root->row.push_back(values[i]);
    }
    calculate_gain_value(root);
    root->child = new node *[root->child_number];

    node *children = new node();
    root->child[0] = children;
    if(root->attribute_number < 4){
        children->internal_class_name = root->row[0].attribute_Info[root->attribute_number]; // Which catagory it divided
        int child_index = 0;
        string first_value = root->row[0].attribute_Info[root->attribute_number];
        for (int i = 0; i < root->row.size(); i++)
        {
            if (root->row[i].attribute_Info[root->attribute_number] == first_value)
            {
                children->row.push_back(root->row[i]);
                children->level=1;
            }
            else
            {

                addChildren(children);


                children = new node();

                children->internal_class_name = root->row[i].attribute_Info[root->attribute_number];
                children->level=1;
                root->child[++child_index] = children;
                children->row.push_back(root->row[i]);
                first_value = root->row[i].attribute_Info[root->attribute_number];
            }
        }
    }
    else if(root->attribute_number >= 4){

        children->internal_class_name = "numericAttribute"+ std::to_string(root->attribute_number) +"<=" + std::to_string(root->Thresold);
        int child_index = 0;
        bool flag = false;

        for (int i = 0; i < root->row.size(); i++)
        {
            if (root->row[i].numericAttribute_Info[root->attribute_number] <= root->Thresold || flag)
            {
                children->row.push_back(root->row[i]);
                children->level=1;
            }
            else
            {

                addChildren(children);

                children = new node();

                children->internal_class_name = "numericAttribute"+ std::to_string(root->attribute_number) +">" + std::to_string(root->Thresold);
                children->level=1;
                root->child[++child_index] = children;
                children->row.push_back(root->row[i]);
                flag = true;
            }
        }

    }
    addChildren(children);
    cout <<"\t"<<root->internal_class_name<<endl;

    for(int cld=0;cld<root->child_number;cld++){

        cout<< root->child[cld]->internal_class_name<<" ";
        if(root->child[cld]->leaf)
            cout<< root->child[cld]->class_name;
        cout<<"     ";

    }
    cout<<endl<<endl;


    //cout <<root->internal_class_name<<" "<< root->child[0]->internal_class_name<<" "<<root->child[1]->internal_class_name<<endl;
    //cout << root->child_number <<endl;
    root->row.clear();
    return root;
}

bool checkSameWinner(node *children)
{
    set<string> temp;
    for (int i = 0; i < children->row.size(); i++)
    {
        temp.insert(children->row[i].winner);
    }

    if (temp.size() == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void addChildren(node *children)
{

    if (checkSameWinner(children)  )
    {
        children->leaf = true;

        children->class_name = children->row[0].winner;

        return;
    }

    children->leaf = false;
    calculate_gain_value(children);

    children->child = new node *[children->child_number];
    node *new_child = new node();

    if(children->attribute_number < 4){
        new_child->internal_class_name = children->row[0].attribute_Info[children->attribute_number];
        new_child->level = children->level+1;
        children->child[0] = new_child;
        int child_index = 0;
        string first_value = children->row[0].attribute_Info[children->attribute_number];
        for (int i = 0; i < children->row.size(); i++)
        {
            if (children->row[i].attribute_Info[children->attribute_number] == first_value)
            {
                new_child->row.push_back(children->row[i]);
            }
            else
            {


                addChildren(new_child);

                new_child = new node();
                new_child->internal_class_name = children->row[i].attribute_Info[children->attribute_number];
                new_child->level = children->level+1;
                children->child[++child_index] = new_child;

                new_child->row.push_back(children->row[i]);
                first_value = children->row[i].attribute_Info[children->attribute_number];
            }
        }
    }
    else if(children->attribute_number >= 4){
        if(children->Thresold ==0 ){
            if(rand()%2==0)
                children->class_name = "Pakistan";
            else
                children->class_name = "India";
            children->leaf=true;
            return;
        }

        new_child->internal_class_name = "numericAttribute"+ std::to_string(children->attribute_number) +"<=" + std::to_string(children->Thresold);

        //cout << new_child->internal_class_name<<endl;

        new_child->level = children->level+1;
        children->child[0] = new_child;

        int child_index = 0;
        bool flag = false;

        for (int i = 0; i < children->row.size(); i++)
        {
            if (children->row[i].numericAttribute_Info[children->attribute_number] <= children->Thresold || flag)
            {
                new_child->row.push_back(children->row[i]);
            }
            else
            {

                addChildren(new_child);
                //cout << new_child->internal_class_name<<endl;

                new_child = new node();
                children->child[++child_index] = new_child;
                new_child->internal_class_name = "numericAttribute"+ std::to_string(children->attribute_number) +">" + std::to_string(children->Thresold);

                //cout << new_child->internal_class_name<<endl;

                new_child->level = children->level+1;
                new_child->row.push_back(children->row[i]);
                flag = true;
            }
        }

    }

    addChildren(new_child);
    cout <<"\t"<<children->internal_class_name<<endl;

    for(int cld=0;cld<children->child_number;cld++){

        cout<< children->child[cld]->internal_class_name<<" ";
        if(children->child[cld]->leaf)
            cout<< children->child[cld]->class_name;
        cout<<"     ";


    }
    cout<<endl<<endl;
    //cout <<children->internal_class_name<<" "<< children->child[0]->internal_class_name<<" "<<children->child[1]->internal_class_name<<endl;
    //cout << children->child_number <<endl;
    children->row.clear();

}


double find_attribute_probability(string num, int index, node *r)
{
    int result = 0;
    for (int i = 0; i < r->row.size(); i++)
    {
        if (r->row[i].attribute_Info[index] == num)
            result++;
    }
    return (double)result;
}

double find_class_probability(string class_value, node *r)
{
    int result = 0;
    for (int i = 0; i < r->row.size(); i++)
    {
        if (r->row[i].winner == class_value)
            result++;
    }
    return (double)result;
}


double find_probability_value(string num, string class_value, int index, node *r)
{
    int result = 0;
    for (int i = 0; i < r->row.size(); i++)
    {
        if (r->row[i].winner == class_value && r->row[i].attribute_Info[index] == num)
            result++;
    }

    return (double)result;
}


int sorting_colum_number;
void sortAttribute(node *r, int column)
{
    sorting_colum_number = column;
    std::sort(r->row.begin(), r->row.end(), [](const row_info &a, const row_info &b)
              { return a.attribute_Info[sorting_colum_number] < b.attribute_Info[sorting_colum_number]; });
}
void sortNumericAttribute(node *r,int column){
    sorting_colum_number = column;
    std::sort(r->row.begin(), r->row.end(), [](const row_info &a, const row_info &b)
              { return a.numericAttribute_Info[sorting_colum_number] < b.numericAttribute_Info[sorting_colum_number]; });

}



void calculate_gain_value(node *row_information)
{
    set<string> qualitativeAttribute_values;
    set<string> class_values;

    double total_row = (double)(row_information->row.size()), heighest_gain_value = 0, t1, t2, t3;
    double entropy = 0, row_entropy;

    for (int p = 0; p < row_information->row.size(); p++)
    {
        class_values.insert(row_information->row[p].winner);
    }

    for (auto &num2 : class_values)
    {
        t1 = find_class_probability(num2, row_information);
        t2 = (t1 / total_row) * (log2(t1 / total_row));
        entropy -= t2;
    }

    for (int i = 0; i < 7; i++)
    {

        if(i < 4){
            for (int p = 0; p < row_information->row.size(); p++)
            {
                qualitativeAttribute_values.insert(row_information->row[p].attribute_Info[i]);
            }
            row_entropy = 0;
            for (auto &num1 : qualitativeAttribute_values)
            {
                double t4 = 0;

                for (auto &num2 : class_values)
                {
                    t2 = find_attribute_probability(num1, i, row_information);
                    t1 = (find_probability_value(num1, num2, i, row_information) / t2);
                    if (t1 == 0)
                        continue;
                    t3 = log2(t1);
                    t4 -= (t1 * t3);
                }
                t2 = (t2 / total_row);
                row_entropy += (t2 * t4);
            }
        }

        else if(i >= 4){

            sortNumericAttribute(row_information, i);

            double lowestEntropy = 5;
             row_entropy = 0;
            for(int q=0;q< row_information->row.size();q++){



                    double t4 = 0;

                        t2 = q+1;

                        t1=0;
                        int s;
                        for( s=0;s<t2;s++){
                            if (row_information->row[s].winner == "India" ){
                                t1++;
                            }
                        }

                        if(t1==0 || t1==t2)
                            continue;
                        t3 = - ((t1/t2) * log2(t1/t2) + ((t2-t1)/t2)*log2((t2-t1)/t2));
                        t3 = ((q+1)/total_row)*t3;
                        t1=0;
                        t2= row_information->row.size() - t2;
                        for(  ;s<row_information->row.size();s++){
                            if (row_information->row[s].winner == "India" ){
                                t1++;
                            }
                        }
                        if(t1==0 || t1==t2)
                            continue;
                        t4 = - ((t1/t2) * log2(t1/t2) + ((t2-t1)/t2)*log2(((t2-t1)/t2)));
                        t4 = (t2/total_row)*t4;
                        double t5 = t3 + t4;
                        if(t5 < lowestEntropy ){
                            lowestEntropy=t5;

                            row_information->thresold[i] = row_information->row[q].numericAttribute_Info[i];
                            row_entropy = t5;
                        }



            }

        }

        if ((entropy - row_entropy) > heighest_gain_value && i<4)
        {
            heighest_gain_value = (entropy - row_entropy);
            row_information->attribute_number = i;
            row_information->child_number = qualitativeAttribute_values.size();
        }
        else if((entropy - row_entropy) > heighest_gain_value){
            heighest_gain_value = (entropy - row_entropy);
            row_information->attribute_number = i;
            row_information->child_number = 2;
            row_information->Thresold = row_information->thresold[i];
        }

        qualitativeAttribute_values.clear();
    }
    if(row_information->attribute_number < 4)
        sortAttribute(row_information, row_information->attribute_number);
    else{
       sortNumericAttribute(row_information, row_information->attribute_number);
    }
}

string find_decision(node *level_data, row_info test_data)
{


    string ch;
    int i = 0;
    if (level_data->leaf )
    {
        //cout<<"leaf\n";

            ch = level_data->class_name;
            //cout <<level_data->class_name<<endl;

    }
    else
    {

        if(level_data->attribute_number < 4){

            for (i = 0; i < level_data->child_number; i++)
            {

                if (level_data->child[i]->internal_class_name == test_data.attribute_Info[level_data->attribute_number])
                {
                    ch = find_decision(level_data->child[i], test_data);
                    break;
                }


            }
            if (i == level_data->child_number)
                ch = find_decision(level_data->child[i - 1], test_data);
        }
        else{


                if((test_data.numericAttribute_Info[level_data->attribute_number] <= level_data->Thresold) ){
                    string childName = "numericAttribute"+ std::to_string(level_data->attribute_number) +"<=" + std::to_string(level_data->Thresold);
                    if(level_data->child[0]->internal_class_name == childName){

                        ch = find_decision(level_data->child[0], test_data);

                    }
                    else{
                       ch = find_decision(level_data->child[1], test_data);
                    }

                }
                else{
                    string childName = "numericAttribute"+ std::to_string(level_data->attribute_number) +">" + std::to_string(level_data->Thresold);
                    if(level_data->child[0]->internal_class_name == childName){
                        ch = find_decision(level_data->child[0], test_data);

                    }
                    else{
                       ch = find_decision(level_data->child[1], test_data);
                    }
                }

            }
    }

    return ch;
}

bool testing(node *root, row_info test_data)
{
    string ch = find_decision(root, test_data);

    if (ch == test_data.winner)
    {
        //cout<<"true"<<endl;
        return true;
    }
    else
    {
        return false;
    }
}

int Prediction()
{
    node *roots;
    load_all_data();

    load_data(1209);

    roots = create_tree();


    int match = 0, disMatch = 0;

    for (int i = 30; i < MAX_DATA; i++)
    {

        if (testing(roots, values[i]))
            match++;
        else
            disMatch++;
    }

    cout << match << " " << disMatch << endl;
    double Accuracy = (double)(match ) / (double)(match + disMatch);
    cout << "Accuracy is: " << Accuracy * 100 << endl<<endl;
    row_info Current_match;
    int option;

    cout << "To predict a match enter  all attribute value in the formate:"<<endl;
    cout <<"TossWinner , TossDecission , City , Stadium , 1stInningsTotalRun , 1stInningsTotalWicket , RequiredRunRate  "<<endl;
    while(1){
        int i=0;
        cout <<"Do you want to predict one: (press (1)) ";
        cin >> option;
        if(option != 1)
            break;
        for( i=0;i<4;i++)
            cin >> Current_match.attribute_Info[i];
        while(i<7){
            cin >> Current_match.numericAttribute_Info[i];
            i++;
        }
        string ch = find_decision(roots, Current_match);
        cout <<"\n\n\n"<<"Predicted Team:  "<<ch<<"\n\n\n" <<endl;
    }

    return 0;
}


#endif // RANDOMDECISSIONTREE_H_INCLUDED
