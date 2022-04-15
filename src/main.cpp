#include <iostream>
#define U64 unsigned long long

// Right shift = closer to start
// Left shift = closer to end
enum board_tiles {
    a8,b8,c8,d8,e8,f8,g8,h8,
    a7,b7,c7,d7,e7,f7,g7,h7,
    a6,b6,c6,d6,e6,f6,g6,h6,
    a5,b5,c5,d5,e5,f5,g5,h5,
    a4,b4,c4,d4,e4,f4,g4,h4,
    a3,b3,c3,d3,e3,f3,g3,h3,
    a2,b2,c2,d2,e2,f2,g2,h2,
    a1,b1,c1,d1,e1,f1,g1,h1,
    };

enum { white, black };

U64 bishop_mask[64];
U64 rook_mask[64];
U64 queen_mask[64];

const U64 not_a_bitboard = 18374403900871474942ULL;
const U64 not_h_bitboard = 9187201950435737471ULL;
const U64 not_ab_bitboard = 18229723555195321596ULL;
const U64 not_gh_bitboard = 4557430888798830399ULL;
const U64 rook_magic[64] = {
        0x2080020500400f0ULL,
        0x28444000400010ULL,
        0x20000a1004100014ULL,
        0x20010c090202006ULL,
        0x8408008200810004ULL,
        0x1746000808002ULL,
        0x2200098000808201ULL,
        0x12c0002080200041ULL,
        0x104000208e480804ULL,
        0x8084014008281008ULL,
        0x4200810910500410ULL,
        0x100014481c20400cULL,
        0x4014a4040020808ULL,
        0x401002001010a4ULL,
        0x202000500010001ULL,
        0x8112808005810081ULL,
        0x40902108802020ULL,
        0x42002101008101ULL,
        0x459442200810c202ULL,
        0x81001103309808ULL,
        0x8110000080102ULL,
        0x8812806008080404ULL,
        0x104020000800101ULL,
        0x40a1048000028201ULL,
        0x4100ba0000004081ULL,
        0x44803a4003400109ULL,
        0xa010a00000030443ULL,
        0x91021a000100409ULL,
        0x4201e8040880a012ULL,
        0x22a000440201802ULL,
        0x30890a72000204ULL,
        0x10411402a0c482ULL,
        0x40004841102088ULL,
        0x40230000100040ULL,
        0x40100010000a0488ULL,
        0x1410100200050844ULL,
        0x100090808508411ULL,
        0x1410040024001142ULL,
        0x8840018001214002ULL,
        0x410201000098001ULL,
        0x8400802120088848ULL,
        0x2060080000021004ULL,
        0x82101002000d0022ULL,
        0x1001101001008241ULL,
        0x9040411808040102ULL,
        0x600800480009042ULL,
        0x1a020000040205ULL,
        0x4200404040505199ULL,
        0x2020081040080080ULL,
        0x40a3002000544108ULL,
        0x4501100800148402ULL,
        0x81440280100224ULL,
        0x88008000000804ULL,
        0x8084060000002812ULL,
        0x1840201000108312ULL,
        0x5080202000000141ULL,
        0x1042a180880281ULL,
        0x900802900c01040ULL,
        0x8205104104120ULL,
        0x9004220000440aULL,
        0x8029510200708ULL,
        0x8008440100404241ULL,
        0x2420001111000bdULL,
        0x4000882304000041ULL,
};

const U64 bishop_magic[64] = {
        0x100420000431024ULL,
        0x280800101073404ULL,
        0x42000a00840802ULL,
        0xca800c0410c2ULL,
        0x81004290941c20ULL,
        0x400200450020250ULL,
        0x444a019204022084ULL,
        0x88610802202109aULL,
        0x11210a0800086008ULL,
        0x400a08c08802801ULL,
        0x1301a0500111c808ULL,
        0x1280100480180404ULL,
        0x720009020028445ULL,
        0x91880a9000010a01ULL,
        0x31200940150802b2ULL,
        0x5119080c20000602ULL,
        0x242400a002448023ULL,
        0x4819006001200008ULL,
        0x222c10400020090ULL,
        0x302008420409004ULL,
        0x504200070009045ULL,
        0x210071240c02046ULL,
        0x1182219000022611ULL,
        0x400c50000005801ULL,
        0x4004010000113100ULL,
        0x2008121604819400ULL,
        0xc4a4010000290101ULL,
        0x404a000888004802ULL,
        0x8820c004105010ULL,
        0x28280100908300ULL,
        0x4c013189c0320a80ULL,
        0x42008080042080ULL,
        0x90803000c080840ULL,
        0x2180001028220ULL,
        0x1084002a040036ULL,
        0x212009200401ULL,
        0x128110040c84a84ULL,
        0x81488020022802ULL,
        0x8c0014100181ULL,
        0x2222013020082ULL,
        0xa00100002382c03ULL,
        0x1000280001005c02ULL,
        0x84801010000114cULL,
        0x480410048000084ULL,
        0x21204420080020aULL,
        0x2020010000424a10ULL,
        0x240041021d500141ULL,
        0x420844000280214ULL,
        0x29084a280042108ULL,
        0x84102a8080a20a49ULL,
        0x104204908010212ULL,
        0x40a20280081860c1ULL,
        0x3044000200121004ULL,
        0x1001008807081122ULL,
        0x50066c000210811ULL,
        0xe3001240f8a106ULL,
        0x940c0204030020d4ULL,
        0x619204000210826aULL,
        0x2010438002b00a2ULL,
        0x884042004005802ULL,
        0xa90240000006404ULL,
        0x500d082244010008ULL,
        0x28190d00040014e0ULL,
        0x825201600c082444ULL,
};
void print_bitboard(U64 bitboard) {
    for (int rank = 0; rank < 8; rank++){
        std::cout << -(rank-8) << "  ";
        for (int file = 0; file < 8; file++){
            int square  = rank * 8 + file;
            int check = (bitboard & (1ULL << square) ) ? 1:0 ;
            std::cout << check << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n   a b c d e f g h" << "\n\n";
}

U64 set_bit(U64 bitboard, int tile) {
    return bitboard | (1ULL << tile);
}

int get_bit(U64 bitboard, int tile) {
    return bitboard & (1ULL << tile) ? 1 : 0;
}

U64 del_bit(U64 bitboard, int tile) {
    return bitboard & (1ULL << tile) ? bitboard ^ (1ULL << tile) : 0;
}

U64 generate_pawn_attack_mask(int square, int color){

    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);

    // White pawn
    if (!color) {
        attacks =  attacks | (not_a_bitboard & bitboard) >> 9;
        attacks =  attacks | (not_h_bitboard & bitboard) >> 7;
    } else {
        attacks = attacks | (not_a_bitboard & bitboard) << 7;
        attacks = attacks | (not_h_bitboard & bitboard) << 9;
    }
    return attacks;
}

U64 generate_knight_attack_mask(int square, int color){
    // Knight movements from Top left -> Bottom right
    // 17,15 ,10 ,6, -6, -10, -15, -17


    // White pawn
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);

    // Top- left
    attacks =  attacks | (not_a_bitboard & bitboard) >> 17;
    attacks =  attacks | (not_ab_bitboard & bitboard) >> 10;
    // Top right
    attacks =  attacks | (not_gh_bitboard & bitboard) >> 6;
    attacks =  attacks | (not_h_bitboard & bitboard) >> 15;
    // Bottom-left
    attacks =  attacks | (not_ab_bitboard & bitboard) << 6;
    attacks =  attacks | (not_a_bitboard & bitboard) << 15;
    // Bottom-right
    attacks =  attacks | (not_gh_bitboard & bitboard) << 10;
    attacks =  attacks | (not_h_bitboard & bitboard) << 17;

    return attacks;
}

U64 generate_king_attack_mask(int square, int color){
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);

    // Right shifts
    attacks =  attacks | (not_a_bitboard & bitboard) >> 9;
    attacks =  attacks | bitboard >> 8;
    attacks =  attacks | (not_h_bitboard & bitboard) >> 7;
    attacks =  attacks | (not_a_bitboard & bitboard) >> 1;

    attacks =  attacks | (not_h_bitboard & bitboard) << 1;
    attacks =  attacks | (not_a_bitboard & bitboard) << 7;
    attacks =  attacks | bitboard << 8;
    attacks =  attacks | (not_h_bitboard & bitboard) << 9;

    return attacks;
}

void generate_bishop_rays() {
    // Loop through all the tiles
    for (int square = 0; square < 64; square++) {
        U64 attacks = 0ULL;

        int trow = square / 8;
        int tfile = square % 8;
        int row,file;

        // South-East mask
        for (row = trow+1, file = tfile +1; row<=6 && file <= 6; row++, file++) attacks |= (1ULL << (row * 8 +file));
        // South-West mask
        for (row = trow+1, file = tfile -1; row<=6 && file >= 1; row++, file--) attacks |= (1ULL << (row * 8 +file));
        // North-West mask
        for (row = trow-1, file = tfile -1; row>=1 && file >= 1; row--, file--) attacks |= (1ULL << (row * 8 +file));
        // North-East mask
        for (row = trow-1, file = tfile +1; row>=1 && file <= 6; row--, file++) attacks |= (1ULL << (row * 8 +file));
        bishop_mask[square] = attacks;
        queen_mask[square] |= attacks;
    }

}

void generate_rook_rays() {
    // Loop through all the tiles
    for (int square = 0; square < 64; square++) {
        U64 attacks = 0ULL;

        int actual_row = square / 8;
        int actual_file = square % 8;
        int row,file;

        // North mask
        for (row = actual_row-1; row>=1; row--) attacks |= (1ULL << (row * 8 +actual_file));

        // East mask
        for (file = actual_file+1; file<=6; file++) attacks |= (1ULL << (actual_row * 8 +file));

        // South mask
        for (row = actual_row+1; row<=6; row++) attacks |= (1ULL << (row * 8 +actual_file));
        // West mask

        for (file = actual_file-1; file>=1; file--) attacks |= (1ULL << (actual_row * 8 +file));

        rook_mask[square] = attacks;
        queen_mask[square] |= attacks;
    }

}


int main() {
    U64 new_bitboard = 0ULL;
    generate_bishop_rays();
    generate_rook_rays();
    print_bitboard(bishop_mask[d4]);
    print_bitboard(rook_mask[d4]);
    print_bitboard(queen_mask[d4]);
//    new_bitboard = generate_king_attack_mask(h8,  white);
//    print_bitboard(new_bitboard);

    return 0;
}