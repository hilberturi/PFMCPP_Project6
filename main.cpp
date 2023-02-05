/*
 Project 6: Part 1 / 2
 Video: Chapter 3 Part 2

Create a branch named Part1

Purpose:  This project will show you the difference between member functions and static class functions, as well as the difference between pointers and references and the code semantics that accompany pointers and references.

 Pointers

 Please look at the screenshot in the files to see what happens if you paste this assignment into an existing cpp file in an xcode project
 
 Task: replace all of the <#place holder#> placeholders with proper names and types that will make this program compile and run.
 
 press the Compile, link and run... button and work your way through all of the error messages.
 

 steps:
 
 1) finish implementing the constructor for T. the constructor parameters need to initialize 2) and 3)
 
 2) provide a member variable in T of a type of your choosing that works with the compare function below T
         note the name of the variable used in the compare function
 
 3) provide a member variable of type std::string in T that works with the *first* cout statement in main().
         note the name of the variable used in the *first* cout statement in main()
 
 4) finish defining the struct with the compare function
 5) provide proper types for the arguments to compare, and a proper return value
         be sure to make it work with the pointer semantics being used in the if statements.
         see 8) for a hint about what type to use.
 
 6) finish instantiating the two T instances being declared in main(), based on the constructor you finished implementing in T
     Their names (line 105,106) are different than the member variables names (line 77), even tho the placeholders share the same name.
     Don't let this confuse you.
 
 7) Declare 'f' with the proper type so the call to f.compare works
 
 8) call f.compare() with the correct arguments, based on 2) and 5)
 
 9) correct the cout that uses smaller's member variable with some safe pointer usage.
    the possible return values of the compare() function should give you a hint.
    Also: if smaller == nullptr, make the cout statement explain the reasons that `f.compare()` might return nullptr.  
    hint: There are multiple reasons
 
 10) complete the implementation for the static function in <structName2>
 
 11) call the <structName2> static function correctly in main()
 
 12) replicate the functionality of <structName2>'s static function by implementing a member function in U that does the same thing.
 
 13) remember the rules for using pointers!  What is the one thing we always do before we use a pointer?
 
 After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
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
    T* compare(T* a, T* b) //5
    {
        // I will enforce safe pointer usage here as directed by 13)
        if (a != nullptr && b != nullptr)
        {
            if( a->value < b->value ) return a;
            if( a->value > b->value ) return b;
        }
        return nullptr;
    }
};

struct U
{
    float exactTargetValue { 0 }, adjustedValue { 0 };
    float updateValuesAndMultiply(float* updatedValue)      //12
    {
        // Note: I could have replaced 'that' by 'this' here but I deciced to use
        // plain member access without this->
        // obviously a nullptr check for this is not necessary so I have deleted this
        // check from the code that I copied from the static method.
        
        // check for nullptr as guided by 13)
        if (updatedValue == nullptr)
        {
            std::cout << "U::updateValuesAndMultiply(): cannot update for nullptr" << std::endl;
        }
        else
        {
            std::cout << "U's exactTargetValue value: " << exactTargetValue << std::endl;
            exactTargetValue = *updatedValue;
            std::cout << "U's exactTargetValue updated value: " << exactTargetValue << std::endl;
            while( std::abs(adjustedValue - exactTargetValue) > 0.001f )
            {
                /*
                 write something that makes the distance between that->adjustedValue and that->exactTargetValue get smaller
                 */
                adjustedValue += 0.5f * (exactTargetValue - adjustedValue);
            }
            std::cout << "U's adjustedValue updated value: " << adjustedValue << std::endl;
        }
        return adjustedValue * exactTargetValue;
    }
};

struct UValueUpdater
{
    static float updateValuesAndMultiply(U* that, float* updatedValue )        //10
    {
        // check for nullptr as guided by 13)
        if (that == nullptr)
        {
             std::cout << "UValueUpdater::updateValuesAndMultiply(): unable to update for that==nullptr"   
                          ", returning 0" 
                       << std::endl;
            return 0;
        }
        if (updatedValue == nullptr)
        {
            std::cout << "U::updateValuesAndMultiply(): cannot update for nullptr" << std::endl;
        }
        else 
        {
            std::cout << "U's exactTargetValue value: " << that->exactTargetValue << std::endl;
            that->exactTargetValue = *updatedValue; // I had to add * here in addition to substituting the placeholder
            std::cout << "U's exactTargetValue updated value: " << that->exactTargetValue << std::endl;
            while( std::abs(that->adjustedValue - that->exactTargetValue) > 0.001f )
            {
                /*
                 write something that makes the distance between that->adjustedValue and that->exactTargetValue get smaller
                 */
                that->adjustedValue += 0.5f * (that->exactTargetValue - that->adjustedValue);
            }
            std::cout << "U's adjustedValue updated value: " << that->adjustedValue << std::endl;
        }
        return that->adjustedValue * that->exactTargetValue;
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
    auto* smaller = f.compare( &t1, &t2);                              //8
    if (smaller != nullptr)
    {
        std::cout << "the smaller one is << " << smaller->name << std::endl; //9    
    }
    else 
    {
        std::cout << "'f.compare()' returned nullptr (at least one arg is nullptr, or both args have same value)"
                  << std::endl;
    }
    
    U u1;
    float updatedValue = 5.f;
    std::cout << "[static func] u1's multiplied values: " << UValueUpdater::updateValuesAndMultiply( &u1, &updatedValue) << std::endl;                  //11
    
    U u2;
    std::cout << "[member func] u2's multiplied values: " << u2.updateValuesAndMultiply( &updatedValue ) << std::endl;
}
