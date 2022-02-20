#include <iostream>
#include<string>
#include<array_list.h>
#include<gtest\gtest.h>

using namespace std;


TEST(ArrayList, StringStream)
{
    cout << "\nTest the ArrayList methods: Append, Insert, Remove_all\n";

    ssuds::ArrayList<int> ilist;

    stringstream ss; 
    ss << ilist; 

    EXPECT_EQ(ss.str(), "[]");
    ss.str("");
    ss.clear();

    ilist.append(4);
    ss << ilist;
    EXPECT_EQ(ss.str(), "[4]");

    ss.str("");
    ss.clear();
    ilist.append(7);
    ss << ilist;
    EXPECT_EQ(ss.str(), "[4,7]");

    ss.str("");
    ss.clear();
    ilist.insert(2,1);
    ss << ilist;
    EXPECT_EQ(ss.str(), "[4,2,7]");

    ss.str("");
    ss.clear();
    ilist.append(2);
    ilist.remove_all(2);
    ss << ilist;
    EXPECT_EQ(ss.str(), "[4,7]");

    ss.str("");
    ss.clear();
    ssuds::ArrayList<int> ilist2(move(ilist));
    ss << ilist2;
    EXPECT_EQ(ss.str(), "[4,7]");

    int result = 0;
    try
    {
        ilist2.remove(5);
    }
    catch (out_of_range)
    {
        result = 1;
    }

    EXPECT_EQ(result, 1);


}

TEST(ArrayList, BracketOperator)
{
    cout << "\nTest the Bracket Operator\n";

    ssuds::ArrayList<int> ilist;

    ilist.append(5);
    

    EXPECT_EQ(ilist[0], 5);


    int result = 0; 
    try
    {
        ilist[1];
    }
    catch (out_of_range)
    {
        result = 1;
    }

    EXPECT_EQ(result, 1);

}

TEST(ArrayList, IntializerList)
{
    cout << "\nTest the initializer list constructor\n";


    ssuds::ArrayList<int> ilist3 = {1,2,3};
    stringstream ss;
    ss << ilist3;

    EXPECT_EQ(ss.str(), "[1,2,3]");


}

TEST(ArrayList, ReverseArrayList)
{
    cout << "\nTest the reverse Iterator\n";

    ssuds::ArrayList<float> flist;
    flist.append(1.1f);
    flist.append(2.2f);
    flist.append(3.3f);
    flist.append(4.4f);

    ssuds::ArrayList<float>::ArrayListIterator it;

    it = flist.rbegin();
    EXPECT_EQ(*it, 4.4f);

    ++it;
    EXPECT_EQ(*it, 3.3f);

    it = flist.rbegin() + 2;
    EXPECT_EQ(*it, 2.2f);

    it = flist.rend();
    EXPECT_EQ(*it, 1.1f);
        
}


TEST(ArrayList, CompareIterators)
{
    cout << "\nCompare two Operators\n";

    ssuds::ArrayList<float> flist;
    flist.append(1.1f);
    flist.append(2.2f);

    ssuds::ArrayList<float>::ArrayListIterator it;
    it = flist.rbegin();

    ssuds::ArrayList<float>::ArrayListIterator it2;
    it2 = flist.begin();

    int result = 0;

    if (it != it2)
        result = 1;

    EXPECT_EQ(result, 1);



}

TEST(ArrayList, IteratorTest)
{
    cout << "\nTest the manual and the for-each loop methods\n";
    ssuds::ArrayList<float> flist;
    flist.append(4.4f);
    flist.append(5.5f);
    flist.append(6.6f);
    ssuds::ArrayList<float>::ArrayListIterator it;

    it = flist.begin();

    int i = 0;

    while (it != flist.end() )
    {
    
        EXPECT_EQ(*it, flist[i]);
        ++it;
        ++i;
    }

    int j = 0;

    for (float f : flist) {
        ASSERT_EQ(f, flist[j]);
        j++;
    }

}

int main(int argc, char** argv) {
    
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}
