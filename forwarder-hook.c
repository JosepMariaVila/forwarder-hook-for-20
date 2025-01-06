/**
 * This hook resend the amount from a payment received or a URI buy to the destinations saved in the namespace of the hooks account.
 * The hook accepts 20 destinations and it will divide the initial amount among the destinations.
 * You can add destinations to the namespaces
 * Hook Parameters to Add destinations using Invoke
 * ADD: Xahau Address transformed  from rAddress To Account ID. You can use https://hooks.services/tools/raddress-to-accountid or https://transia-rnd.github.io/xrpl-hex-visualizer/ . To check if you are doing it right, address: rBnGX5KRERL2vMtZU2hDpF4osbhvichmvn will be translated to 6E7FE2948037180F3646CC248FAF2BCACD59893C
 * NUM: The number to identify the address and be able to delete it (Only accepts from 00 to ...)

 * Hook Parameters to delete destinations using Invoke
 * DEL: Number (from 00 to ...)

 You can check the status of your namespace visiting https://xahau-testnet.xrplwin.com/ checking your hook account

 * This is a small example, probably it's not the best way to code this Hook. Please, verify everything before using it.
 */
#include "hookapi.h"

int64_t hook(uint32_t reserved)
{
    // I create a 20 (?) txn reserve for PREPARE_PAYMENT_SIMPLE
    etxn_reserve(20);

    // Counters to know how many address I have in the namespace and divide the final amount
    uint8_t count[1] = {0x00U};
    uint8_t divide[1] = {0x00U};

    // Declare the keywords for the Hook Params
    uint8_t num_param[3] = {'N', 'U', 'M'};
    uint8_t add_param[3] = {'A', 'D', 'D'};
    uint8_t del_param[3] = {'D', 'E', 'L'};

    uint8_t add_buf[20] = {0x00U};
    uint8_t del_buf[20] = {0x00U};
    uint8_t num_buf[20] = {0x00U};

    uint8_t account01[20] = {0x00U};
    uint8_t account02[20] = {0x00U};
    uint8_t account03[20] = {0x00U};
    uint8_t account04[20] = {0x00U};
    uint8_t account05[20] = {0x00U};
    uint8_t account06[20] = {0x00U};
    uint8_t account07[20] = {0x00U};
    uint8_t account08[20] = {0x00U};
    uint8_t account09[20] = {0x00U};
    uint8_t account10[20] = {0x00U};
    uint8_t account11[20] = {0x00U};
    uint8_t account12[20] = {0x00U};
    uint8_t account13[20] = {0x00U};
    uint8_t account14[20] = {0x00U};
    uint8_t account15[20] = {0x00U};
    uint8_t account16[20] = {0x00U};
    uint8_t account17[20] = {0x00U};
    uint8_t account18[20] = {0x00U};
    uint8_t account19[20] = {0x00U};
    uint8_t account20[20] = {0x00U};

    // Check destination of the original txn
    uint8_t account_field[20];
    int32_t account_field_len = otxn_field(SBUF(account_field), sfDestination);

    // Check hook account
    unsigned char hook_accid[20];
    hook_account((uint32_t)hook_accid, 20);

    // Check hook parameters
    int8_t isNum = otxn_param(num_buf, 1, SBUF(num_param));
    int8_t isAdd = otxn_param(SBUF(add_buf), SBUF(add_param));
    int8_t isDel = otxn_param(del_buf, 1, SBUF(del_param));

    // To know the type of origin txn
    int64_t tt = otxn_type();

    // Check if hook_accid and account_field are the same
    int equal = 0;
    BUFFER_EQUAL(equal, hook_accid, account_field, 20);

    if (!equal && tt == 99 && isAdd == 20 && isNum == 1 && isDel != 1 && num_buf[0] >= 0 && num_buf[0] < 15)
    {
        state_set(SBUF(add_buf), num_buf, 32);
        accept(SBUF("Forwarder: Address added."), 1);
    }
    if (!equal && tt == 99 && isDel == 1 && isAdd != 20 && isNum != 1 && num_buf[0] >= 0 && num_buf[0] < 15)
    {
        state_set(0, 0, del_buf, 32);
        accept(SBUF("Forwarder: Address deleted."), 2);
    }
    if (!equal && tt != 47)
    {
        accept(SBUF("Forwarder: Nothing to do"), 3);
    }
    else
    {

        // fetch the sent Amount
        // Amounts can be 384 bits or 64 bits. If the Amount is an XAH value it will be 64 bits.
        unsigned char amount_buffer[48];
        int64_t amount_len = otxn_field(SBUF(amount_buffer), sfAmount);
        int64_t drops_to_send = 0; // this will be the default

        // No XAH
        if (amount_len != 8)
        {
            accept(SBUF("Forwarder: Nothing to do"), 4);
        }
        else // If it's XAH
        {
            int64_t otxn_drops = AMOUNT_TO_DROPS(amount_buffer);
            drops_to_send = (int64_t)((double)otxn_drops);
            TRACEVAR(otxn_drops);
        }
        // Minimum allowed value to make the Forwarder Hook resend the value
        if (drops_to_send < 10)
        {
            accept(SBUF("Forwarder: No minimum amount. Nothing to do"), 5);
        }
        else
        {
            unsigned char tx01[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx02[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx03[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx04[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx05[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx06[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx07[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx08[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx09[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx10[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx11[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx12[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx13[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx14[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx15[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx16[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx17[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx18[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx19[PREPARE_PAYMENT_SIMPLE_SIZE];
            unsigned char tx20[PREPARE_PAYMENT_SIMPLE_SIZE];

            if (state(SBUF(account01), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account02), count, 32) == 20)
            {
                ++divide[0];
            }

            ++count[0];
            if (state(SBUF(account03), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account04), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account05), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account06), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account07), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account08), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account09), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account10), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account11), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account12), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account13), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account14), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account15), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account16), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account17), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account18), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account19), count, 32) == 20)
            {
                ++divide[0];
            }
            ++count[0];
            if (state(SBUF(account20), count, 32) == 20)
            {
                ++divide[0];
            }

            if (divide[0] == 0)
            {
                accept(SBUF("Forwarder: Empty address list to forward to."), 6);
            }
            else
            {
                PREPARE_PAYMENT_SIMPLE(tx20, drops_to_send / divide[0], account20, 0, 0);
                uint8_t emithash20[32];
                int64_t emit_result20 = emit(SBUF(emithash20), SBUF(tx20));
                
                PREPARE_PAYMENT_SIMPLE(tx19, drops_to_send / divide[0], account19, 0, 0);
                uint8_t emithash19[32];
                int64_t emit_result19 = emit(SBUF(emithash19), SBUF(tx19));
                
                PREPARE_PAYMENT_SIMPLE(tx18, drops_to_send / divide[0], account18, 0, 0);
                uint8_t emithash18[32];
                int64_t emit_result18 = emit(SBUF(emithash18), SBUF(tx18));
                
                PREPARE_PAYMENT_SIMPLE(tx17, drops_to_send / divide[0], account17, 0, 0);
                uint8_t emithash17[32];
                int64_t emit_result17 = emit(SBUF(emithash17), SBUF(tx17));
                
                PREPARE_PAYMENT_SIMPLE(tx16, drops_to_send / divide[0], account16, 0, 0);
                uint8_t emithash16[32];
                int64_t emit_result16 = emit(SBUF(emithash16), SBUF(tx16));
                
                PREPARE_PAYMENT_SIMPLE(tx15, drops_to_send / divide[0], account15, 0, 0);
                uint8_t emithash15[32];
                int64_t emit_result15 = emit(SBUF(emithash15), SBUF(tx15));
                
                PREPARE_PAYMENT_SIMPLE(tx14, drops_to_send / divide[0], account14, 0, 0);
                uint8_t emithash14[32];
                int64_t emit_result14 = emit(SBUF(emithash14), SBUF(tx14));
                
                PREPARE_PAYMENT_SIMPLE(tx13, drops_to_send / divide[0], account13, 0, 0);
                uint8_t emithash13[32];
                int64_t emit_result13 = emit(SBUF(emithash13), SBUF(tx13));
                
                PREPARE_PAYMENT_SIMPLE(tx12, drops_to_send / divide[0], account12, 0, 0);
                uint8_t emithash12[32];
                int64_t emit_result12 = emit(SBUF(emithash12), SBUF(tx12));
                
                PREPARE_PAYMENT_SIMPLE(tx11, drops_to_send / divide[0], account11, 0, 0);
                uint8_t emithash11[32];
                int64_t emit_result11 = emit(SBUF(emithash11), SBUF(tx11));
                
                PREPARE_PAYMENT_SIMPLE(tx10, drops_to_send / divide[0], account10, 0, 0);
                uint8_t emithash10[32];
                int64_t emit_result10 = emit(SBUF(emithash10), SBUF(tx10));

                PREPARE_PAYMENT_SIMPLE(tx09, drops_to_send / divide[0], account09, 0, 0);
                uint8_t emithash09[32];
                int64_t emit_result09 = emit(SBUF(emithash09), SBUF(tx09));

                PREPARE_PAYMENT_SIMPLE(tx08, drops_to_send / divide[0], account08, 0, 0);
                uint8_t emithash08[32];
                int64_t emit_result08 = emit(SBUF(emithash08), SBUF(tx08));

                PREPARE_PAYMENT_SIMPLE(tx07, drops_to_send / divide[0], account07, 0, 0);
                uint8_t emithash07[32];
                int64_t emit_result07 = emit(SBUF(emithash07), SBUF(tx07));

                PREPARE_PAYMENT_SIMPLE(tx06, drops_to_send / divide[0], account06, 0, 0);
                uint8_t emithash06[32];
                int64_t emit_result06 = emit(SBUF(emithash06), SBUF(tx06));

                PREPARE_PAYMENT_SIMPLE(tx05, drops_to_send / divide[0], account05, 0, 0);
                uint8_t emithash05[32];
                int64_t emit_result05 = emit(SBUF(emithash05), SBUF(tx05));

                PREPARE_PAYMENT_SIMPLE(tx04, drops_to_send / divide[0], account04, 0, 0);
                uint8_t emithash04[32];
                int64_t emit_result04 = emit(SBUF(emithash04), SBUF(tx04));

                PREPARE_PAYMENT_SIMPLE(tx03, drops_to_send / divide[0], account03, 0, 0);
                uint8_t emithash03[32];
                int64_t emit_result03 = emit(SBUF(emithash03), SBUF(tx03));

                PREPARE_PAYMENT_SIMPLE(tx02, drops_to_send / divide[0], account02, 0, 0);
                uint8_t emithash02[32];
                int64_t emit_result02 = emit(SBUF(emithash02), SBUF(tx02));

                PREPARE_PAYMENT_SIMPLE(tx01, drops_to_send / divide[0], account01, 0, 0);
                uint8_t emithash01[32];
                int64_t emit_result01 = emit(SBUF(emithash01), SBUF(tx01));

                accept(SBUF("Forwarder: Successful."), 7);
            }
            _g(1, 1); // every hook needs to import guard function and use it at least once
            // unreachable
            return 0;
        }
    }
}
