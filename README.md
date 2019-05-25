# reason-hooks-lib

ReasonML implementation of [`react-hooks-lib`](https://github.com/beizhedenglong/react-hooks-lib).

```reason

[@react.component]
let make = () => {
  open State;
  let {past, present, future, set, undo, redo} = useUndo(0);

  <div>
    {"counter: " |> React.string}
    {present |> string_of_int |> React.string}
    <button onClick={_ => set(prev => prev + 1)}>
      {React.string("+1")}
    </button>
    <button disabled={List.length(past) === 0} onClick={_ => undo()}>
      {React.string("undo")}
    </button>
    <button disabled={List.length(future) === 0} onClick={_ => redo()}>
      {React.string("redo")}
    </button>
  </div>;
};

```


## Testing
If want to test your ReasonReact hooks easily, please take a look at [`reason-hooks-testing-library`](https://github.com/beizhedenglong/reason-hooks-testing-library).
