#ifndef EVENTS_H
#define EVENTS_H


class Events
{
    public:
        Events() {}
        virtual ~Events() {}

        static Events* Instance()
        {
            static Events inst ;
            return &inst ;
        }

        ofEvent<ofColor> ADD_NEW_COLOR ;
        ofEvent<int> REMOVE_LAST_COLOR ;

    protected:
    private:

};

#endif // EVENTS_H
