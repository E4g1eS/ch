const LOG = true;

function log(toLog: any) {
  if (!LOG) return;

  console.log(toLog);
}

enum Color {
  White,
  Black,
}

const UNICODE_REPRESENTATION = {
  "white-king": "\u2654",
  "white-queen": "\u2655",
  "white-rook": "\u2656",
  "white-bishop": "\u2657",
  "white-knight": "\u2658",
  "white-pawn": "\u2659",
  "black-king": "\u265A",
  "black-queen": "\u265B",
  "black-rook": "\u265C",
  "black-bishop": "\u265D",
  "black-knight": "\u265E",
  "black-pawn": "\u265F",
};

class Vector2 {
  x: number;
  y: number;

  constructor(x: number, y: number) {
    this.x = x;
    this.y = y;
  }

  public equals(other: Vector2): boolean {
    return this.x === other.x && this.y === other.y;
  }

  public add(other: Vector2): Vector2 {
    return new Vector2(this.x + other.x, this.y + other.y);
  }
}

interface IPiece {
  getColor(): Color;
  getNotation(): string;
}

abstract class Piece implements IPiece {
  color: Color;

  constructor(color: Color) {
    this.color = color;
  }

  abstract notation(): string;

  public getColor(): Color {
    return this.color;
  }

  public getNotation(): string {
    return this.notation();
  }

  abstract getMoves(position: Vector2, game: Game, board: Board): Vector2[];

  doMove(origin: Vector2, destination: Vector2, game: Game, board: Board): void {
    board.squares[destination.x][destination.y] = board.squares[origin.x][origin.y];
    board.squares[origin.x][origin.y] = null;
    
    if (game.toPlay === Color.White) game.toPlay = Color.Black;
    else game.toPlay = Color.White;
  }

  protected jumpMove(board: Board, destination: Vector2): boolean {
    if (!board.isOnBoard(destination)) return false;

    let destinationPiece = board.squares[destination.x][destination.y];

    if (destinationPiece === null || destinationPiece.color !== this.color)
      return true;

    return false;
  }

  protected slideMove(
    board: Board,
    origin: Vector2,
    offset: Vector2
  ): Vector2[] {
    let moves = new Array<Vector2>();

    let destination = origin.add(offset);

    while (true) {
      if (!board.isOnBoard(destination)) return moves;

      let destinationPiece = board.squares[destination.x][destination.y];

      if (destinationPiece === null || destinationPiece.color !== this.color)
        moves.push(destination);

      if (destinationPiece !== null) return moves;

      destination = destination.add(offset);
    }
  }
}

class King extends Piece {
  getMoves(position: Vector2, game: Game, board: Board): Vector2[] {
    let moves = new Array<Vector2>();

    const offsets = [
      new Vector2(-1, -1),
      new Vector2(-1, 0),
      new Vector2(-1, 1),
      new Vector2(0, -1),
      new Vector2(0, 1),
      new Vector2(1, -1),
      new Vector2(1, 0),
      new Vector2(1, 1),
    ];

    offsets.forEach((offset) => {
      let destination = position.add(offset);
      if (this.jumpMove(board, destination)) moves.push(destination);
    });

    return moves;
  }
  notation(): string {
    return "K";
  }
}

class Queen extends Piece {
  getMoves(position: Vector2, game: Game, board: Board): Vector2[] {
    let moves = new Array<Vector2>();

    moves = moves.concat(this.slideMove(board, position, new Vector2(-1, 0)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(0, -1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(0, 1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(1, 0)));

    moves = moves.concat(this.slideMove(board, position, new Vector2(-1, -1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(-1, 1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(1, -1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(1, 1)));

    return moves;
  }

  notation(): string {
    return "Q";
  }
}
class Rook extends Piece {
  getMoves(position: Vector2, game: Game, board: Board): Vector2[] {
    let moves = new Array<Vector2>();

    moves = moves.concat(this.slideMove(board, position, new Vector2(-1, 0)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(0, -1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(0, 1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(1, 0)));

    return moves;
  }
  notation(): string {
    return "R";
  }
}
class Bishop extends Piece {
  getMoves(position: Vector2, game: Game, board: Board): Vector2[] {
    let moves = new Array<Vector2>();

    moves = moves.concat(this.slideMove(board, position, new Vector2(-1, -1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(-1, 1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(1, -1)));
    moves = moves.concat(this.slideMove(board, position, new Vector2(1, 1)));

    return moves;
  }
  notation(): string {
    return "B";
  }
}
class Knight extends Piece {
  getMoves(position: Vector2, game: Game, board: Board): Vector2[] {
    let moves = new Array<Vector2>();

    const offsets = [
      new Vector2(-2, -1),
      new Vector2(-2, 1),
      new Vector2(-1, -2),
      new Vector2(-1, 2),
      new Vector2(1, -2),
      new Vector2(1, 2),
      new Vector2(2, -1),
      new Vector2(2, 1),
    ];

    offsets.forEach((offset) => {
      let destination = position.add(offset);
      if (this.jumpMove(board, destination)) moves.push(destination);
    });

    return moves;
  }

  notation(): string {
    return "N";
  }
}
class Pawn extends Piece {
  getMoves(position: Vector2, game: Game, board: Board): Vector2[] {
    let moves = new Array<Vector2>();

    let direction = new Vector2(0, 1);
    if (this.color === Color.Black) direction = new Vector2(0, -1);

    //One step forward
    let oneStep = position.add(direction);
    if (
      board.isOnBoard(oneStep) &&
      board.squares[oneStep.x][oneStep.y] === null
    ) {
      moves.push(oneStep);

      //Double step
      let twoStep = oneStep.add(direction);

      log(`${position.y * 2 - 7} === ${direction.y * 5}`);

      if (
        position.y * 2 - 7 === -(direction.y * 5) &&
        board.squares[twoStep.x][twoStep.y] === null
      )
        moves.push(twoStep);
    }

    //Take left
    let takeLeft = position.add(direction).add(new Vector2(-1, 0));
    let takeLeftPiece = board.squares[takeLeft.x][takeLeft.y];
    if (
      (board.isOnBoard(takeLeft) &&
        takeLeftPiece !== null &&
        takeLeftPiece.color !== this.color) ||
      (game.enPassant !== null && game.enPassant.equals(takeLeft)) // en passant
    ) {
      moves.push(takeLeft);
    }

    //Take left
    let takeRight = position.add(direction).add(new Vector2(1, 0));
    let takeRightPiece = board.squares[takeRight.x][takeRight.y];
    if (
      (board.isOnBoard(takeRight) &&
        takeRightPiece !== null &&
        takeRightPiece.color !== this.color) ||
      (game.enPassant !== null && game.enPassant.equals(takeRight))
    ) {
      moves.push(takeRight);
    }

    return moves;
  }
  notation(): string {
    return "P";
  }
}

class Board {
  squares: Array<Array<Piece | null>>;
  readonly size: number;

  constructor() {
    this.size = 8;
    this.initSqaures();
  }

  private initSqaures(): void {
    this.squares = [];
    for (let i = 0; i < this.size; i++) {
      this.squares[i] = [];
      for (let j = 0; j < this.size; j++) {
        this.squares[i][j] = null;
      }
    }
  }

  public defaultPosition(): void {
    this.initSqaures();

    // WHITE
    this.squares[0][0] = new Rook(Color.White);
    this.squares[1][0] = new Knight(Color.White);
    this.squares[2][0] = new Bishop(Color.White);
    this.squares[3][0] = new Queen(Color.White);
    this.squares[4][0] = new King(Color.White);
    this.squares[5][0] = new Bishop(Color.White);
    this.squares[6][0] = new Knight(Color.White);
    this.squares[7][0] = new Rook(Color.White);

    this.squares[0][1] = new Pawn(Color.White);
    this.squares[1][1] = new Pawn(Color.White);
    this.squares[2][1] = new Pawn(Color.White);
    this.squares[3][1] = new Pawn(Color.White);
    this.squares[4][1] = new Pawn(Color.White);
    this.squares[5][1] = new Pawn(Color.White);
    this.squares[6][1] = new Pawn(Color.White);
    this.squares[7][1] = new Pawn(Color.White);

    // BLACK
    this.squares[0][7] = new Rook(Color.Black);
    this.squares[1][7] = new Knight(Color.Black);
    this.squares[2][7] = new Bishop(Color.Black);
    this.squares[3][7] = new Queen(Color.Black);
    this.squares[4][7] = new King(Color.Black);
    this.squares[5][7] = new Bishop(Color.Black);
    this.squares[6][7] = new Knight(Color.Black);
    this.squares[7][7] = new Rook(Color.Black);

    this.squares[0][6] = new Pawn(Color.Black);
    this.squares[1][6] = new Pawn(Color.Black);
    this.squares[2][6] = new Pawn(Color.Black);
    this.squares[3][6] = new Pawn(Color.Black);
    this.squares[4][6] = new Pawn(Color.Black);
    this.squares[5][6] = new Pawn(Color.Black);
    this.squares[6][6] = new Pawn(Color.Black);
    this.squares[7][6] = new Pawn(Color.Black);
  }

  isOnBoard(position: Vector2): boolean {
    return (
      position.x >= 0 &&
      position.y >= 0 &&
      position.x < this.size &&
      position.y < this.size
    );
  }
}

interface IGame {
  newGame(): void;
  size(): number;
  getBoardState(): Array<Array<IPiece | null>>;
  getActiveSquare(): Vector2 | null;
  getAvailableMoves(): Vector2[];
  clicked(position: Vector2): void;
}

class Game implements IGame {
  private board: Board;
  private activeSquare: Vector2 | null;
  public toPlay: Color;

  public enPassant: Vector2 | null;

  constructor() {
    this.board = new Board();
    this.activeSquare = null;
    this.enPassant = null;
    this.toPlay = Color.White;
  }

  public newGame(): void {
    this.board.defaultPosition();
    this.activeSquare = null;
    this.enPassant = null;
    this.toPlay = Color.White;
  }

  public size(): number {
    return this.board.size;
  }

  public getBoardState(): Array<Array<IPiece | null>> {
    return this.board.squares;
  }

  public getActiveSquare(): Vector2 | null {
    return this.activeSquare;
  }

  public getAvailableMoves(): Vector2[] {
    if (this.activeSquare === null) return [];

    let piece = this.board.squares[this.activeSquare.x][this.activeSquare.y];

    if (piece === null) return [];

    let moves = piece.getMoves(this.activeSquare, this, this.board);

    return moves;
  }

  public clicked(position: Vector2): void {
    if (this.activeSquare === null) {
      let clickedPiece = this.board.squares[position.x][position.y];
      if (clickedPiece === null || this.toPlay !== clickedPiece.color) return;

      this.activeSquare = position;
    } else {
      let activeSquare : Vector2 = this.activeSquare; // not nullable
      if (position.equals(this.activeSquare)) {
        this.activeSquare = null;
        return;
      }

      let moves = this.getAvailableMoves();

      moves.forEach(move => {
        if (position.equals(move))
        {
          console.log(`Doing move...`);
          let pieceToMove = this.board.squares[activeSquare.x][activeSquare.y];
          if (pieceToMove === null) throw new Error();
          pieceToMove.doMove(activeSquare, position, this, this.board);
        }
      });

      this.activeSquare = null;
    }
  }
}

class Renderer {
  game: IGame;
  divContainer: HTMLDivElement;
  squares: HTMLDivElement[][];

  constructor(game: IGame, divContainer: HTMLDivElement) {
    this.game = game;
    this.divContainer = divContainer;
    this.initSquares();
  }

  private initSquares(): void {
    let size = this.game.size();
    this.squares = [];

    for (let i = 0; i < size; i++) {
      this.squares[i] = [];

      let column = document.createElement("div");
      column.classList.add("chessboard-column");
      this.divContainer.appendChild(column);

      for (let j = 0; j < size; j++) {
        this.squares[i][j] = document.createElement("div");
        this.squares[i][j].classList.add("chessboard-square");

        if ((i + (j % 2)) % 2 === 0) {
          this.squares[i][j].classList.add("chessboard-square-black");
        } else {
          this.squares[i][j].classList.add("chessboard-square-white");
        }

        this.squares[i][j].addEventListener("click", () => {
          this.clickedAtSquare(new Vector2(i, j));
        });

        column.appendChild(this.squares[i][j]);
      }
    }
  }

  public render(): void {
    let state = this.game.getBoardState();

    let size = this.game.size();
    for (let x = 0; x < size; x++) {
      for (let y = 0; y < size; y++) {
        this.squares[x][y].classList.remove(
          "chessboard-square-highlighted",
          "chessboard-square-available"
        );
        this.renderSquare(this.squares[x][y], state[x][y]);
      }
    }

    let activeSquare = this.game.getActiveSquare();
    if (activeSquare !== null) {
      this.squares[activeSquare.x][activeSquare.y].classList.add(
        "chessboard-square-highlighted"
      );

      let available = this.game.getAvailableMoves();
      available.forEach((element) => {
        this.squares[element.x][element.y].classList.add(
          "chessboard-square-available"
        );
      });
    }

    log(this);
  }

  private renderSquare(square: HTMLDivElement, piece: IPiece | null): void {
    if (piece === null) {
      square.innerText = "";
      square.classList.remove("white-piece");
      square.classList.remove("black-piece");
      return;
    }

    switch (piece.getNotation()) {
      case "K":
        square.innerText = UNICODE_REPRESENTATION["black-king"];
        break;
      case "Q":
        square.innerText = UNICODE_REPRESENTATION["black-queen"];
        break;
      case "R":
        square.innerText = UNICODE_REPRESENTATION["black-rook"];
        break;
      case "B":
        square.innerText = UNICODE_REPRESENTATION["black-bishop"];
        break;
      case "N":
        square.innerText = UNICODE_REPRESENTATION["black-knight"];
        break;
      case "P":
        square.innerText = UNICODE_REPRESENTATION["black-pawn"];
        break;
    }

    switch (piece.getColor()) {
      case Color.White:
        square.classList.remove("black-piece");
        square.classList.add("white-piece");
        break;

      case Color.Black:
        square.classList.add("black-piece");
        square.classList.remove("white-piece");
        break;
    }
  }

  private clickedAtSquare(position: Vector2): void {
    log(`Clicked (${position.x},${position.y})`);
    this.game.clicked(position);
    this.render();
  }
}

let renderer: Renderer;

function main() {
  log("Starting...");

  const game = new Game();
  game.newGame();

  const div = document.createElement("div");
  div.classList.add("chessboard");
  document.body.appendChild<HTMLDivElement>(div);

  renderer = new Renderer(game, div);
  renderer.render();
}

document.addEventListener("DOMContentLoaded", main);
