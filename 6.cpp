#include<bits/stdc++.h>

using namespace std;


class Command {
public:
    virtual void execute() = 0;
};

// Satellite class
class Satellite {
public:
    Satellite() : orientation("North"), solarPanelsActive(false), dataCollected(0) {}

    void rotate(string direction) {
        log("Rotating satellite to " + direction);
        orientation = direction;
    }

    void activatePanels() {
        log("Activating solar panels");
        solarPanelsActive = true;
    }

    void deactivatePanels() {
        log("Deactivating solar panels");
        solarPanelsActive = false;
    }

    void collectData() {
        if (solarPanelsActive) {
            log("Collecting data");
            dataCollected += 10;
        } else {
            throw runtime_error("Cannot collect data when solar panels are inactive");
        }
    }

    string getOrientation() const {
        return orientation;
    }

    bool arePanelsActive() const {
        return solarPanelsActive;
    }

    int getDataCollected() const {
        return dataCollected;
    }

private:
    string orientation;
    bool solarPanelsActive;
    int dataCollected;

    void log(string message) {
        try {
            ofstream logfile("satellite.log", ios_base::app);
            if (logfile.is_open()) {
                logfile << message << endl;
                logfile.close();
            }
        } catch (const exception& e) {
            cerr << "Error writing to log file: " << e.what() << endl;
        }
    }
};

// command for rotating the satellite
class RotateCommand : public Command {
public:
    RotateCommand(string direction, class Satellite* satellite) : direction(direction), satellite(satellite) {}

    void execute() override {
        try {
            satellite->rotate(direction);
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            ofstream errorfile("command_error.log", ios_base::app);
            if (errorfile.is_open()) {
                errorfile << e.what() << endl;
                errorfile.close();
            }
        }
          catch (...) {
            cerr << "Transient error occurred during rotate command execution" << endl;
        }
    }

private:
    string direction;
    class Satellite* satellite;
};

// command for activating the solar panels
class ActivatePanelsCommand : public Command {
public:
    ActivatePanelsCommand(class Satellite* satellite) : satellite(satellite) {}

    void execute() override {
        try {
            satellite->activatePanels();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            ofstream errorfile("command_error.log", ios_base::app);
            if (errorfile.is_open()) {
                errorfile << e.what() << endl;
                errorfile.close();
            }
        }
          catch (...) {
            cerr << "Transient error occurred during activate command execution" << endl;
        }
    }

private:
    class Satellite* satellite;
};

// command for deactivating the solar panels
class DeactivatePanelsCommand : public Command {
public:
    DeactivatePanelsCommand(class Satellite* satellite) : satellite(satellite) {}

    void execute() override {
        try {
            satellite->deactivatePanels();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            ofstream errorfile("command_error.log", ios_base::app);
            if (errorfile.is_open()) {
                errorfile << e.what() << endl;
                errorfile.close();
            }
        }
          catch (...) {
            cerr << "Transient error occurred during deactivate command execution" << endl;
        }
    }

private:
    class Satellite* satellite;
};

// command for collecting data
class CollectDataCommand : public Command {
public:
    CollectDataCommand(class Satellite* satellite) : satellite(satellite) {}

    void execute() override {
        try {
            satellite->collectData();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            ofstream errorfile("satellite_error.log", ios_base::app);
            if (errorfile.is_open()) {
                errorfile << e.what() << endl;
                errorfile.close();
            }
        }
        catch (...) {
            cerr << "Transient error occurred during  collect command execution" << endl;
        }
    }

private:
    class Satellite* satellite;
};

// Invoker class for executing commands
class CommandInvoker {
public:
    void setCommand(Command* command) {
        this->command = command;
    }

    void executeCommand() {
        try {
            command->execute();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            ofstream errorfile("command_error.log", ios_base::app);
            if (errorfile.is_open()) {
                errorfile << e.what() << endl;
                errorfile.close();
            }
        }
        catch (...) {
            cerr << "Transient error occurred during command execution" << endl;
        }
    }

private:
    Command* command;
};



// Main function
int main() {
    // Initialize satellite
    Satellite satellite;

    // Initialize command invoker
    CommandInvoker invoker;

    // Execute commands
    string input;
    while (true) {
        cout << "Enter command (rotate, activate, deactivate, collect, exit): ";
        cin >> input;

        if (input == "rotate") {
            cout << "Enter direction (North, South, East, West): ";
            cin >> input;
            if(input=="North" || input=="N" ||input=="n"){
                invoker.setCommand(new RotateCommand("North", &satellite));
            }
            else if(input=="South" || input=="S" ||input=="s"){
                invoker.setCommand(new RotateCommand("South", &satellite));
            }
            else if(input=="East" || input=="E" ||input=="e"){
                invoker.setCommand(new RotateCommand("East", &satellite));
            }
            else if(input=="West" || input=="W" ||input=="w"){
                invoker.setCommand(new RotateCommand("West", &satellite));
            }
            else{
                cout<<"Wrong Direction is Entered";
            }
            invoker.executeCommand();
        } else if (input == "activate") {
            invoker.setCommand(new ActivatePanelsCommand(&satellite));
            invoker.executeCommand();
        } else if (input == "deactivate") {
            invoker.setCommand(new DeactivatePanelsCommand(&satellite));
            invoker.executeCommand();
        } else if (input == "collect") {
            invoker.setCommand(new CollectDataCommand(&satellite));
            invoker.executeCommand();
        } else if (input == "exit") {
            break;
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }

    // Print final state
    cout << "Orientation: " << satellite.getOrientation() << endl;
    cout << "Solar Panels: " << (satellite.arePanelsActive() ? "Active" : "Inactive") << endl;
    cout << "Data Collected: " << satellite.getDataCollected() << endl;

    return 0;
}