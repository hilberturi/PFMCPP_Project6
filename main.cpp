/*
 Project 6: Part 2 / 2
 Video: Chapter 3 Part 3

Create a branch named Part2

 References
 
 
 1) convert the pointer usage (except for 'const char*') to reference types or 
    const reference types **>>> WHERE POSSIBLE <<<**
    Not every pointer can be converted.
        hint: There is no reference equivalent to nullptr.  
        if a pointer (including nullptr) is being returned anywhere, don't try to convert it to a reference.

    You have to ask yourself if each pointer can be converted to a (const) reference.
    Think carefully when making your changes.

 2) revise the 'else' statement in main() that handles when `smaller` is a nullptr. 
 there is only one reason for `compare` to return nullptr. 
 Update this std::cout expression to specify why nullptr was returned.
 
 3) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 */


#include <iostream>
#include <string>
struct T
{
    T(int v, const char* theName) : value(v), name(theName) {}  //1 Note that I had to change the <#type name#> of the first arg to int rather than T*
    int value; //2
    std::string name; //3
};

struct TPtrComparator                                //4
{
    const T* compare(const T& a, const T& b) //5
    {
        if( a.value < b.value ) return &a;
        if( a.value > b.value ) return &b;        
        return nullptr;
    }
};

struct U
{
    float exactTargetValue { 0 }, adjustedValue { 0 };
    // I'll use a const ref for a primitive type rather than passing it by value as requested in Pt.2:
    float updateValuesAndMultiply(const float& updatedValue)      //12
    {       
        std::cout << "U's exactTargetValue value: " << exactTargetValue << std::endl;
        exactTargetValue = updatedValue;
        std::cout << "U's exactTargetValue updated value: " << exactTargetValue << std::endl;
        while( std::abs(adjustedValue - exactTargetValue) > 0.001f )
        {
            /*
             write something that makes the distance between that->adjustedValue and that->exactTargetValue get smaller
             */
            adjustedValue += 0.5f * (exactTargetValue - adjustedValue);
        }
        std::cout << "U's adjustedValue updated value: " << adjustedValue << std::endl;
    return adjustedValue * exactTargetValue;
    }
};

struct UValueUpdater
{
    // I'll use a const ref for a primitive type rather than passing it by value as requested in Pt.2:
    static float updateValuesAndMultiply(U& that, const float& updatedValue )        //10
    {
        std::cout << "U's exactTargetValue value: " << that.exactTargetValue << std::endl;
        that.exactTargetValue = updatedValue; // I had to add * here in addition to substituting the placeholder
        std::cout << "U's exactTargetValue updated value: " << that.exactTargetValue << std::endl;
        while( std::abs(that.adjustedValue - that.exactTargetValue) > 0.001f )
        {
            /*
             write something that makes the distance between that->adjustedValue and that->exactTargetValue get smaller
             */
            that.adjustedValue += 0.5f * (that.exactTargetValue - that.adjustedValue);
        }
        std::cout << "U's adjustedValue updated value: " << that.adjustedValue << std::endl;
        return that.adjustedValue * that.exactTargetValue;
    }
};
        
/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

int main()
{
    T t1(1 , "name1");                                             //6
    T t2(2 , "name2");                                             //6
    
    TPtrComparator f;                                            //7
    auto* smaller = f.compare (t1, t2);                              //8
    if (smaller != nullptr)
    {
        std::cout << "the smaller one is << " << smaller->name << std::endl; //9    
    }
    else 
    {
        std::cout << "'f.compare()' returned nullptr (both args have same value)"
                  << std::endl;
    }
    
    U u1;
    float updatedValue = 5.f;
    std::cout << "[static func] u1's multiplied values: " << UValueUpdater::updateValuesAndMultiply (u1, updatedValue) << std::endl;                  //11
    
    U u2;
    std::cout << "[member func] u2's multiplied values: " << u2.updateValuesAndMultiply (updatedValue) << std::endl;
}
