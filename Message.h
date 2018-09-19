#ifndef MESSAGE_H
#define MESSAGE_H
#define MAXNAMELEN 32

enum ObjectDesc
{
        Human,
        NonHuman,
        Vehicle,
        StaticObject
};

enum ObjectForm
{
        Cube,
        Sphere,
        Pyramid,
        Cone
};

// Message type Change (Server -> Client)
enum ChangeType
{
        NewPlayer,
        PlayerLeave,
        NewPlayerPosition
};

// Messages of type Event (Client -> Server)
enum EventType
{
        Move
};

//Message head
enum MsgType
{
        Join,	// Client joining game at server
        Leave, // Client leaving game
        Change, // Information to clients
        Event, // Information from clients to server
        TextMessage // Send text messages to one or all
};

//player position
struct Coordinate
{
        int x;
        int y;
};

//Included first in all messages
struct MsgHead
{
    unsigned int length; //Total message length
    unsigned int seq_no; //Sequence number
    unsigned int id; //Client ID or 0;
    enum MsgType type; //Type of message
};

// Message type Join (Client -> Server)
struct JoinMsg
{
    struct MsgHead head;
    enum ObjectDesc desc;
    enum ObjectForm form;
    char name[MAXNAMELEN];	// nullterminated!, or empty
};

//Message type Leave (Client -> Server)
struct LeaveMsg
{
    struct MsgHead head;
};

// Included first in all Change messages
struct ChangeMsg
{
    struct MsgHead head;
    enum ChangeType type;
};

// Variations of ChangeMsg
struct NewPlayerMsg
{
    struct ChangeMsg msg; //Change message header with new client id
    enum ObjectDesc desc;
    enum ObjectForm form;
    char name[MAXNAMELEN]; // nullterminated!, or empty
};

struct PlayerLeaveMsg
{
    struct ChangeMsg msg; //Change message header with new client id
};

struct NewPlayerPositionMsg
{
    struct ChangeMsg msg; //Change message header
    struct Coordinate pos; //New object position
    struct Coordinate dir; //New object direction
};

//Included first in all Event messages
struct EventMsg
{
    struct MsgHead head;
    enum EventType type;
};

//Variantions of EventMsg
struct MoveEvent
{
    struct EventMsg event;
    struct Coordinate pos; //New object position
    struct Coordinate dir; //New object direction
};

//Messages of type TextMessage
struct TextMessageMsg // Optional at client side!!!
{
    struct MsgHead head;
    char text[1]; // NULL-terminerad array av chars.
};

#endif // MESSAGE_H
