open Jest;
open Expect;
open ReasonHooksTestingLibrary.Testing;

describe("useDidMount", () => {
  open Lifecycle;
  open State;
  open Result;
  let useDidMountTest = () => {
    let {count, inc} = useCounter(0);
    useDidMount(() => {
      inc();
      None;
    });
    count;
  };
  let container = renderHook(() => useDidMountTest(), ());
  test("count is 0", () =>
    expect(container->result->current) |> toBe(1)
  );
});