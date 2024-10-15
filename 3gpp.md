# 一 38413 

## 1.1 PDU Session Management Procedures

### 1.1.1 PDU Session Resource Notify

#### 1触发条件 ：

   PDU 会话资源通知流程的目的是通知特定 UE 已建立的 QoS 流量或 PDU 会话已被 NG-RAN 节点释放、不再满足或再次满足，为此请求通知控制。它还用于通知 NG-RAN 节点未成功接受路径切换请求过程中更新的 QoS 参数。该消息是由基站发送给核心网的。简单的说就是这个消息是基站给核心网带来两种类型的信息一种是PDU释放列表，一种是通知列表，分别反映的NG-RAN已经释放了该PDU会话QOS流量不在满足以及再次满足的情况。

![image-20241008105455394](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20241008105455394.png)

#### 2代码处理：

AMF会根据PDU Notify列表中的释放列表，以及通知列表，构造相应的消息，smInfoType分为Release和notify，AMF构造Sm_Update_SmContext消息发送给SMF。

## 1.2PDU Session Resource Modification

### 1触发条件：

| 1    | QoS需求的变化，例如带宽要求增加或减少。              |
| ---- | ---------------------------------------------------- |
| 2    | 用户服务类型变化，如视频通话或在线游戏。             |
| 3    | 网络环境变化，如用户在切换基站时，可能需要调整资源。 |

PDUmodification可以通过三个实体触发，分别是AMF，RAN，UE。

| UE   | UE 通过一个NAS消息 PDU Session Modification Request |
| :--- | --------------------------------------------------- |
| AMF  | 这个是后加的R16应该是没有的                         |
| RAN  | AN触发的代码中其实没实现/好像被删除了               |

![image-20241008160142553](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20241008160142553.png)

UE触发的PDU的Modify，首先UE向AMF发送了NAS消息 PDU Session Modification Request，当AMF接收到该消息之后，向SMF发送Update SM Context消息，（code的处理）AMF将N1Sm payload container缓存，然后将消息发送，SMF接受到该消息之后，进行响应，然后需要携带N1SMMsg和N2SM MSG。AMF接受到SMF的RSP之后需要，分别获取N1消息和N2消息。然后给UE发送N1 NAS消息 PDU Session Modification Command，同时发送N2 PDU_MODIFY_Resource_Remote_Request,当基站接受到来自AMF的Modify Resource Remote Request请求之后，不需要等到UE 回复Modification Compelete直接发送消息Modify Resource Remote Response给AMF。AMF然后发送Update SMContext消息给SMF，当SMF接受到该消息之后，成功回复应该是204不带n1和n2消息。当UE 回复pdu command complete。这个消息标志着QOS的信息已经改了，进行确认。AMF将这个SM Container发送给SMF，SMF进行响应。

SMF触发的mod 是PCF或者UDM等导致的，N1 N2 消息应该和3a类似

# 二 23502 

### Identity Request

identity Request的消息当UE_CONTEXT_TRANSFER_RSP消息之后，如果此时没有SUCI的信息，则AMF需要去请求UE，IdentityRequest消息，UE会返回IdentityRsp消息，然后将SUCI的信息带给AMF。另外在UE_CONTEXT_TRANSFER_UPDP_REQ之后，AMF会根据是否存在PEI的信息，如果没有PEI的信息，则会请求UE，PEI的信息。另外就是在鉴权的时候，如果RES*和XRES*的信息不一致，而且终端是带着GUTI注册的，这个时候AMF会向UE请求SUCI重新鉴权。

PEI包括IMEI和IMEIsv，IMEIsv是IMEI的扩展，包含了软件的相关信息

