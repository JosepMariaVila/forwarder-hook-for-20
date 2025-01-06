
## Forwarder Hook for 20 Xahau Network
This is a example to demonstrate the use of a working hook in Xahau. The hook is programmed in C. It is recommended for educational purposes only. The creator is not responsible for any problems it may cause.

**Please use new accounts to test this hook and test everything beforehand on Testnet just in case. I am not responsible for any losses. Create your own code if you are not sure.**

## What does the Forwarder Hook do?

The hook is installed on an account. Once installed, every time the account receives a payment through a Payment or URITokenBuy transaction type, it will be distributed among the accounts stored in the account namespace. If there are no accounts in the namespace, it will do nothing.

## Attention

This hook or other installed hooks could change the expected result. So it is important to pre-test this and other hooks on Testnet before using it on Mainnet.

## How to install the Forwarder Hook on Testnet?

HookOn is activated to trigger for Invoke, Payment and URIToken_Buy. You can verify it copying the HookOn value (FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFFFF7FFFFFBFFFFE) in this website: https://richardah.github.io/xrpl-hookon-calculator/

    const prepared = {
      "TransactionType": "SetHook",
      "Account": your_account_address,
      "Flags": 0,
      "Hooks": [
        {
          "Hook": {
            "HookHash": "1A9D1EEA98A9BE3C45A35872E51E36B6E73CBB7033A96CE0D98DB484215E0494",
            "HookNamespace": "0000000000000000000000000000000000000000000000000000000000000000",
            "HookOn": "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFFFF7FFFFFBFFFFE",
          }
        }
      ],
      ...networkInfo.txValues,
    };

## How to uninstall the Forwarder Hook on Mainnet/Testnet?

    const prepared = {
      "TransactionType": "SetHook",
      "Account": your_account_address,
      "Flags": 0,
      Hooks:
    [        
        {                        
            Hook: {
                CreateCode: "",
                Flags: 1,
            }
        }
    ],
      ...networkInfo.txValues,
    };

## How to add addresses?

The hook allows up to 20 addresses to which the amounts received can be distributed in equal parts. They will be registered with an identifier from 00 to 19. The addresses must be converted to Account ID. To do this you can use the following services:

- https://hooks.services/tools/raddress-to-accountid 

To check if you are doing it right, address: rBnGX5KRERL2vMtZU2hDpF4osbhvichmvn will be translated to 6E7FE292948037180F3646CC248FAF2BCACD59893C

**Visual representation of the namespace or address book:**

|identifier|address|
|-----------|-------|
|01|address1 translated to AccountID|
|02|address2 translated to AccountID|
|03|address3 translated to AccountID|
|..|..                              |
|20|address20 translated to AccountID|

To add an account we must create an Invoke transaction from the hook account and add the following Hook parameters and values:

ADD with the AccountID
NUM with the position we want between 00 to 19

**Example:**

- ADD: D53F733E54B866B9FBDB85762071832B03A56C76
- NUM: 00

We need to change ADD and NUM keywords to hex. ADD = 414444 and NUM = 4E554D.
Also, we need to translate address account rLSYATPWj9UECGBEeVpxwEN16CuEREK3uR to AccountID D53F733E54B866B9FBDB85762071832B03A56C76

- 414444: D53F733E54B866B9FBDB85762071832B03A56C76
- 4E554D: 00

    const prepared = {
      TransactionType: "Invoke",
      Account: your_account_address,
      Flags: 0,
      HookParameters: [
        {
          HookParameter: {
            HookParameterName: "414444",
            HookParameterValue: "D53F733E54B866B9FBDB85762071832B03A56C76",
          },
        },
        {
          HookParameter: {
            HookParameterName: "4E554D",
            HookParameterValue: "00",
          },
        },
      ],
      ...networkInfo.txValues,
    };

## How to delete addresses?

To delete you have to create an Invoke transaction from the hook account and use as parameter DEL and the position between 00 to 19 as value. In case there is any address registered with that identifier, it will delete it.

DEL and the position we want to delete between 00 to 19

**Example:**

- DEL: 00

We need to translate DEL keyword to hex. 

- DEL = 44454C

Numbers from 00 to 19 stay the same. No need to translate them.

    const prepared = {
      TransactionType: "Invoke",
      Account: your_account_address,
      Flags: 0,
      HookParameters: [
        {
          HookParameter: {
            HookParameterName: "44454C",
            HookParameterValue: "00",
          }
        },
      ],
      ...networkInfo.txValues,
    };


## How to install the Forwarder Hook on Mainnet?

Same as Testnet but changing the hookhash. The Hookhash is D22582E8BAF59FC682DEF490A3992CADB3CD5CCE851FB358B2DE299ABE30DB9E.

    const prepared = {
      "TransactionType": "SetHook",
      "Account": your_account_address,
      "Flags": 0,
      "Hooks": [
        {
          "Hook": {
            "HookHash": "D22582E8BAF59FC682DEF490A3992CADB3CD5CCE851FB358B2DE299ABE30DB9E",
            "HookNamespace": "0000000000000000000000000000000000000000000000000000000000000000",
            "HookOn": "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFFFF7FFFFFBFFFFE",
          }
        }
      ],
      ...networkInfo.txValues,
    };

## Video Tutorial (pending)

I created a video tutorial to learn how to use this hook on Xahau Testnet: [https://www.youtube.com/watch?v=rf8zSmrZkPA](https://www.youtube.com/watch?v=rf8zSmrZkPA)

## Credit

This hook was originally created by @[ekiserrepe](https://x.com/ekiserrepe). You can find more of his projects on [ekiserrepe.com](https://www.ekiserrepe.com)
