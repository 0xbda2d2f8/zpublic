#include "venus_net/venus_net.h"
#include "protocol/protocol.h"
#include "protocol/opcodes.h"
#include "game_common/game_define.h"

enum TestCaseType
{
    TC_CONCURRENCY_TESTING,         //�����Ӳ������ԣ������������Ͽ���
    TC_CONNECTION_STRESS_TESTING,   //������ѹ�����ԣ��������Ӻ������ɳ����������Ͽ���
};

class TestCaseRunner
{
public:
    virtual void run() = 0;
};

class GameMessageHandler : public MessageHandler
{
public:
    virtual void onConnected()
    {
        printf("client has been connected to server.\n");
    }

    virtual void onMessage(uint16 opcode, const NetworkPacket::Ptr& message)
    {
        printf("onMessage() : [opcode = %d]\n", opcode);

        switch (opcode)
        {
        case Opcodes::SCGetRandomNameRsp:
            {
                Protocol::SCGetRandomNameRsp response;
                DECODE_MESSAGE(response, message);
                printf("Get random nickname = %s", response.random_name.c_str());
                break;
            }
        default:
            break;
        }
    }

    virtual void onShutdown()
    {
        printf("disconnected.\n");
    }
};

int main(int argc, char** argv)
{
    Poco::Net::SocketAddress serverAddress("127.0.0.1:36911");
    GameMessageHandler handler;

    const int client_count = 100;
    TcpClient tcpClient(handler);

    try
    {
        std::cout << "starting.." << std::endl;
        for (int i = 0; i < 1; i++)
        {
            tcpClient.connect(serverAddress);

			/*Protocol::CSRegisterReq registerRequest;
			registerRequest.username = "138001655_2@qq.com";
			registerRequest.password = "e10adc3949ba59abbe56e057f20f883e";
			tcpClient.sendMessage(Opcodes::CSRegisterReq, registerRequest);*/

            Protocol::CSGetRandomNameReq getNicknameRequest;
            getNicknameRequest.gender = GENDER_FEMALE;
            tcpClient.sendMessage(Opcodes::CSGetRandomNameReq, getNicknameRequest);

            //Protocol::CSLoginReq loginRequest;
            //loginRequest.account = "138001655@qq.com";
            //loginRequest.password = "e10adc3949ba59abbe56e057f20f883e";
            //tcpClient.sendMessage(Opcodes::CSLoginReq, loginRequest);

            //loginRequest.account = "powman";
            //loginRequest.password = "demaciaaaaa";
            //tcpClient.sendMessage(Opcodes::CSLoginReq, loginRequest);

            //tcpClient.close();
        }

        std::cout << "finished." << std::endl;
    }
    catch (const Poco::Exception& e)
    {
        std::cout << e.displayText() << std::endl;
    }

    getchar();
    return 0;
}