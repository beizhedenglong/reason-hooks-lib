[@react.component]
let make = () => {
  open State;
  let {count, set} = useCounter(0);

  <div>
    {"count: " |> React.string}
    {count |> string_of_int |> React.string}
    {count < 3 ? <UseWillUnmoutExample /> : React.null}
    <UseDidUpdateExample count />
    <button onClick={_ => set(prev => prev + 1)}>
      {React.string("+1")}
    </button>
    <button onClick={_ => set(prev => prev - 1)}>
      {React.string("-1")}
    </button>
  </div>;
};