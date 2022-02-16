#include<iostream>
#include<list>

using namespace std;

class DataLog
{
private:
    list<int> logList;
    list<int>::iterator currentState;

public:
    DataLog();
    DataLog(const int& data);
    void addCurrentState(int number);
    void subtractCurrentState(int number);
    void save();
    void undo();
    void redo();

    int getCurrentStateData()
    {
        return *currentState;
    }

    void printLog()
    {
        for (auto i = logList.begin(); i != logList.end(); i++) {
            if (i == currentState) cout << "Current state: ";
            cout << "[ " << *i << " ] => ";
        }
        cout << "END_LOG";
    }
};

DataLog::DataLog()
{
    /*
     * TODO:  add the first state with 0
     */
    logList.push_front(0);
    this->currentState = logList.begin();
}

DataLog::DataLog(const int& data)
{
    /*
     * TODO:  add the first state with data
     */
    logList.push_front(data);
    this->currentState = logList.begin();
}

void DataLog::addCurrentState(int number)
{
    /*
     * TODO: Increase the value of current state by number
     */
    //logList.push_back((*currentState) += number);
    int temp = *currentState + number;
    *currentState = temp;
}

void DataLog::subtractCurrentState(int number)
{
    /*
     * TODO: Decrease the value of current state by number
     */
    //logList.push_back((*currentState) -= number);
    int temp = *currentState - number;
    *currentState = temp;
}

void DataLog::save()
{
    /*
     * TODO: This function will create a new state, copy the data of the currentState
     *       and move the currentState Iterator to this new state. If there are other states behind the
     *       currentState Iterator, we delete them all before creating a new state.
     */
    //list<int>::iterator end = logList.end();
    //currentState = --end;
    
    // ---------------------------------------------
    while (logList.back() != *currentState) {  //(!this->logList.empty()) || (--this->logList.end() != this->currentState)
        this->logList.pop_back();
    }
    int num = *(this->currentState);
    this->logList.push_back(num);
    this->currentState = --logList.end();

    //---
    /*
    while (logList.back() != *currentState)
        logList.pop_back();
    int Newnum = *currentState;
    logList.push_back(Newnum);
    currentState = --logList.end();
    */
}

void DataLog::undo()
{
    /*
     * TODO: Switch to the previous state of the data
     *       If this is the oldest state in the log, nothing changes
     */
    if (!(this->currentState == this->logList.begin())) {
        this->currentState--;
    }
}

void DataLog::redo()
{
    /*
     * TODO: Switch to the latter state of the data
     *       If this is the latest state in the log, nothing changes
     */
    if (!(this->currentState == --this->logList.end())) {
        this->currentState++;
    }
}


int main() {
    DataLog log(10);
    log.save();
    log.addCurrentState(15);
    log.save();
    log.addCurrentState(15);
    log.save();
    log.undo();
    log.undo();
    log.undo();
    log.undo();
    log.printLog();
    cout << "\n";
    log.save();
    log.printLog();
	return 0;
}