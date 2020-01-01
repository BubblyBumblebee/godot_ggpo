#ifndef GODOTGGPO_H
#define GODOTGGPO_H

#include <ggponet.h>

#include <inttypes.h>

#include "core/object.h"
#include "core/reference.h"
#include "core/dictionary.h"

#include "callbacks.h"

class GGPO: public Object {
    GDCLASS(GGPO, Object)

public:
    enum {
        PLAYERTYPE_LOCAL, PLAYERTYPE_REMOTE, PLAYERTYPE_SPECTATOR,
        MAX_PLAYERS = 4, MAX_PREDICTION_FRAMES = 8, MAX_SPECTATORS = 32,
        OK = 0, INVALID_HANDLE = -1,
        ERRORCODE_SUCCESS = 0, ERRORCODE_GENERAL_FAILURE = -1, ERRORCODE_INVALID_SESSION = 1, ERRORCODE_INVALID_PLAYER_HANDLE = 2, ERRORCODE_PLAYER_OUT_OF_RANGE = 3, ERRORCODE_PREDICTION_THRESHOLD = 4, ERRORCODE_UNSUPPORTED = 5, ERRORCODE_NOT_SYNCHRONIZED = 6, ERRORCODE_IN_ROLLBACK = 7, ERRORCODE_INPUT_DROPPED = 8, ERRORCODE_PLAYER_DISCONNECTED = 9, ERRORCODE_TOO_MANY_SPECTATORS = 10, ERRORCODE_INVALID_REQUEST = 11,
        EVENTCODE_CONNECTED_TO_PEER = 1000, EVENTCODE_SYNCHRONIZING_WITH_PEER = 1001, EVENTCODE_SYNCHRONIZED_WITH_PEER = 1002, EVENTCODE_RUNNING = 1003, EVENTCODE_DISCONNECTED_FROM_PEER = 1004, EVENTCODE_TIMESYNC = 1005, EVENTCODE_CONNECTION_INTERRUPTED = 1006, EVENTCODE_CONNECTION_RESUMED = 1007
    };
    static GGPO* get_singleton();
    GGPO();
    ~GGPO();

    void start_session(const String& game, int numPlayers, int localPort);
    void start_spectating(const String& game, int numPlayers, int localPort, const String& hostIp, int hostPort);
    void set_disconnect_notify_start(int timeout);
    void set_disconnect_timeout(int timeout);
    void synchronize_input(int inputs, int length, int disconnectFlags);
    void add_local_input(int localPlayerHandle, uint64_t input);
    void close_session();
    void idle(int timeout);
    void add_player(int playerType, int playerNum, const String& playerIpAddress, int playerPort, int pHandle);
    void disconnect_player(int pHandle);
    void set_frame_delay(int pHandle, int frameDelay);
    void advance_frame();
    void log(const String& text);
    Dictionary get_network_stats(int pHandle);

    GGPOSession* get_ggpoptr() {
        return GGPOPtr;
    }
    void set_ggpoptr(GGPOSession* ggpo) {
        GGPOPtr = ggpo;
    }

protected:
    static void _bind_methods();
    static GGPO* singleton;

    GGPOSession* GGPOPtr = NULL;
};

#endif //GODOTGGPO_H