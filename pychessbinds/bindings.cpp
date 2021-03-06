#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <string>
#include "move_analyser.hpp"
#include "position.hpp"

namespace py = pybind11;

int black = C_BLACK;
int white = C_WHITE;

PYBIND11_MODULE(libpychess, m) {
    m.doc() = "Interface definitions for the C++ library pychesslib.";
    
    // Define the module constants for black and white pieces
    m.attr("BLACK") = black;
    m.attr("WHITE") = white;
    
    // Define some high level piece constructors
    m.def_submodule("pieces")
        .def("Piece",  &Piecedef::BasePiece,             
             py::arg("colour"),
             py::arg("starting_position"),
             py::arg("kind"),
             py::arg("max_distance") = 7,
             py::arg("projections") = std::nullopt,
             py::arg("is_active") = true,             
             py::return_value_policy::reference, "Return a new Piece")
        .def("King",   &Piecedef::King,   py::return_value_policy::reference, "Return a new king")
        .def("Queen",  &Piecedef::Queen,  py::return_value_policy::reference, "Return a new queen")
        .def("Rook",   &Piecedef::Rook,   py::return_value_policy::reference, "Return a new rook")
        .def("Bishop", &Piecedef::Bishop, py::return_value_policy::reference, "Return a new bishop")
        .def("Knight", &Piecedef::Knight, py::return_value_policy::reference, "Return a new knight")
        .def("Pawn",   &Piecedef::Pawn,   py::return_value_policy::reference, "Return a new pawn");

    // Define the piece class wrapper
    py::class_<Piece>(m, "Piece")
        .def(py::init<Position, const char, const bool, int, const ProjectionSet>())
        .def("__repr__", [](const Piece& p){return "<Piece " + std::string{p.kind} + " colour: " + std::to_string(p.colour) + " at " + std::to_string(p.position.i) + ", " + std::to_string(p.position.j) + ">";})
        .def("__hash__", &Piece::hash)
        .def("__eq__", &Piece::operator==)
        .def_readwrite("is_active",   &Piece::is_active)
        .def_readonly("colour",      &Piece::colour)
        .def_readonly("kind",        &Piece::kind)
        .def_readonly("distance",    &Piece::distance)
        .def_readonly("position",    &Piece::position)
        .def_readonly("projections", &Piece::projections);

    // Define the vector and position class wrappers
    py::class_<Vec>(m, "Vec")
        .def(py::init<const int, const int>())
        .def("__repr__", [](const Vec& v){return "<Vector " + std::to_string(v.i) + ", " + std::to_string(v.j) + ">";})
        .def("__mul__", &Vec::operator*)
        .def("__add__", &Vec::operator+)
        .def("__sub__", &Vec::operator-)
        .def("__eq__", &Vec::operator==)
        .def("__ne__", &Vec::operator!=)
        .def_readonly("i", &Vec::i)
        .def_readonly("j", &Vec::j);
    
    py::class_<Position>(m, "Position")
        .def(py::init<int, int>())
        .def(py::init<const std::string>())
        .def("__add__", &Position::operator+)
        .def("__sub__", &Position::operator-)
        .def("__eq__", &Position::operator==)
        .def("__ne__", &Position::operator!=)
        .def("__repr__", &Position::__repr__)
        .def("__hash__", &Position::__hash__)
        .def("is_valid", &Position::is_valid)
        .def("path_to", &Position::path_to)
        .def("algebraic", &Position::algebraic)
        .def_readonly("i", &Position::i)
        .def_readonly("j", &Position::j);
    
    // Define the MoveAnalyser wrapper (using pybind stl conversions)
    py::class_<MoveAnalyser>(m, "MoveAnalyser")
        .def(py::init<const PieceVec&, const Position&>())
        .def("PsuedolegalMoves", &MoveAnalyser::PsuedolegalMoves);
};
