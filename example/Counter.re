[@react.component]
let make = () => {
  open State;
  let {counter, set} = useCounter(0);

  <div>
    {"counter: " |> React.string}
    {counter |> string_of_int |> React.string}
    <button onClick={_ => set(prev => prev + 1)}>
      {React.string("+1")}
    </button>
    <button onClick={_ => set(prev => prev - 1)}>
      {React.string("-1")}
    </button>
  </div>;
};