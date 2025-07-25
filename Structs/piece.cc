
Colour oppositeColour(Colour c) {
    switch (c) {
        case Colour::Black: return Colour::White;
        case Colour::White: return Colour::Black;
        default:
            throw std::invalid_argument("oppositeColour(): Input colour must be White or Black");
    }
}

