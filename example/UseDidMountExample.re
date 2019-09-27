[@react.component]
let make = () => {
  open State;
  open Lifecycle;
  let {count, inc} = useCounter(0);
  useDidMount(() => {
    Js.log("hello");
    None;
  });
  <div onClick={_ => inc()}> {React.string(count |> string_of_int)} </div>;
};