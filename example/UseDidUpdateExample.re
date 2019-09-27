[@react.component]
let make = (~count) => {
  Lifecycle.(
    useDidUpdate(
      () => {
        Js.log("did update");
        None;
      },
      [|count|],
    )
  );
  React.null;
};