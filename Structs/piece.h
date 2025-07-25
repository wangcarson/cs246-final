

// Empty and invalid piece constants
const Piece EMPTY_PIECE{PieceType::Empty, Colour::None};

enum class PieceType { Pawn, Rook, Bishop, Knight, King, Queen, Empty };
enum class Colour { White = 1, Black = -1, None = 0 };

struct Piece {
    PieceType type;
    Colour colour;
    // removed Tile

    bool isKing() const { return type == PieceType::King; }
    bool isQueen() const { return type == PieceType::Queen; }
    bool isRook() const { return type == PieceType::Rook; }
    bool isBishop() const { return type == PieceType::Bishop; }
    bool isKnight() const { return type == PieceType::Knight; }
    bool isPawn() const { return type == PieceType::Pawn; }
    bool isEmpty() const { return type == PieceType::Empty; }

    bool isColour(Colour c) const { return colour == c; }
    bool isOppositeColour(Colour c) const { return colour == oppositeColour(c); }

    bool operator==(const Piece& other) const {
        return (colour == other.colour) && (type == other.type);
    }
    // required for map
    bool operator<(const Piece& other) const {
        if (colour != other.colour)
            return colour < other.colour;
        return type < other.type;
    }
};

// Helper functions with colours and pieces.
Colour oppositeColour(Colour c);
Piece parsePiece(char s);
char getPieceChar(Piece p);

std::ostream &operator<<(std::ostream &out, const Piece &p);
std::ostream &operator<<(std::ostream &out, const PieceType &p);
std::ostream &operator<<(std::ostream &out, const Colour &c);
